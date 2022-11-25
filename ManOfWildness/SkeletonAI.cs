using System.Collections;
using UnityEngine;

public class SkeletonAI : MonoBehaviour
{
    [SerializeField] AudioSource skeletonAudioSource;

    public GameObject attackPrefab;

    public enum State
    {
        IDLE,
        TRACE,
        AVOID,
        ATTACK
    }

    State state = State.TRACE;

    public bool isSkeletonDead  = false;
    bool isPlayerDead    = false;
    bool detectCampFire  = false;

    float distFromPlayer;
    float attackDist    = 7.0f;     // 공격 사정거리
    float avoidingDist  = 35.0f;    // avoiding모드로 전환하기위해 측정
    float fireAreaDist  = 30.0f;    // 불쪽으로 일정간격 안으로 못오게 하기위함
    float avoidFireDist = 20.0f;    // 횃불을 들고 다가갔을 때 일정간격 이하일 경우 도망가게 하기 위함

    public float walkSpeed = 5.0f;
    float runSpeed = 20.0f;

    float rayRange  = 150.0f;
    float rayOffset = 1.5f;     //기준축에서 위쪽으로

    int playerLayer;
    int obstacleLayer;
    int layerMask;
    
    WaitForSeconds coroutineTime;   //코루틴에서 사용할 지연시간 변수
    WaitForSeconds attackTime;

    Transform           playerTr;
    Animator            animator;
    SkeletonMovement    skeletonMovement;
    PlayerMovement      playerMovement;
    PlayerState         playerState;

    readonly int hashIsAttack   = Animator.StringToHash("IsAttack");
    readonly int hashDead       = Animator.StringToHash("Dead");
    readonly int hashMove       = Animator.StringToHash("Move");
    readonly int hashSpeed      = Animator.StringToHash("Speed");
    readonly int hashIsIdle     = Animator.StringToHash("IsIdle");

    float elapsedTime = 0;
    float durableTime = 5.0f;

    private void Start()
    {
		animator            = GetComponent<Animator>();
		skeletonMovement    = GetComponent<SkeletonMovement>();

		attackTime      = new WaitForSeconds(2.0f);      //코루틴의 지연시간 생성
        coroutineTime   = new WaitForSeconds(0.3f);

		var player = GameManager.Instance.Player;
        if (player != null)
        {
            playerState = player.GetComponent<PlayerState>();
            playerState.OnPlayerDeath += StopAttackingDeadPlayer;

            playerTr = player.GetComponent<Transform>();
            playerMovement = player.GetComponent<PlayerMovement>();
        }

        EarthRevolution.Instance.OnSwitchedTime += SkeletonDie;
        AudioManager.Instance.OnSFXVolumeChanged += SkeletonVolumeChange;

        //레이어 마스크 값 계산
        playerLayer     = LayerMask.NameToLayer("Player");
        obstacleLayer   = LayerMask.NameToLayer("Obstacle");
        layerMask = 1 << playerLayer | 1 << obstacleLayer;

        StartCoroutine(CheckState());
        StartCoroutine(Action());

    }

    IEnumerator CheckState()
    {
        yield return new WaitForSeconds(1.0f);  //오브젝트 풀에 생성 시 다른 스크립트의 초기화를 위해 대기

        //해골전사가 사망하기 전까지 도는 무한루프
        while (!isSkeletonDead && !isPlayerDead)
        {
            if (playerState.HoldingTorch && distFromPlayer <= avoidFireDist * avoidFireDist && !isSkeletonDead)
            {
                while (distFromPlayer <= avoidingDist * avoidingDist && !isSkeletonDead)
                {
                    state = State.AVOID;
                    yield return null;
                }
            }

            if (playerState.InCampFire && GameManager.Instance.campFire != null)
            {
                if (Vector3.SqrMagnitude(GameManager.Instance.campFire.transform.position - transform.position) <= fireAreaDist * fireAreaDist)
                {
                    detectCampFire = true;
                }
                else
                {
                    detectCampFire = false;
                }
            }

		    if (playerState.HoldingTorch && distFromPlayer <= fireAreaDist * fireAreaDist && !isSkeletonDead || 
                playerState.InCampFire && detectCampFire)
            {
                 state = State.IDLE;
            }
            else
            {
                state = State.TRACE;
            }
            yield return coroutineTime;
        }
    }

    IEnumerator Action()
    {
        yield return new WaitForSeconds(4.0f);

        animator.SetTrigger(hashMove);

        //동물이 사망할 때까지 무한루프
        while (!isSkeletonDead && !isPlayerDead)
        {
            //상태에 따라 분기 처리
            switch (state)
            {
                case State.IDLE:

                    skeletonMovement.Stop();
                    animator.SetBool(hashIsIdle, true);
                    break;

                case State.TRACE:

                    animator.SetBool(hashIsAttack, false);
                    animator.SetBool(hashIsIdle, false);

                    if (playerMovement.IsRunning)
                    {
                        animator.SetFloat(hashSpeed, runSpeed);
                        skeletonMovement.ChaseTarget(playerTr.transform.position, runSpeed);
                    }
                    else
                    {
                        animator.SetFloat(hashSpeed, walkSpeed);
                        skeletonMovement.ChaseTarget(playerTr.transform.position, walkSpeed);
                    }
                    break;

                case State.AVOID:

                    skeletonMovement.RunAway((transform.position - playerTr.position).normalized, runSpeed);
                    animator.SetBool(hashIsAttack, false);
                    animator.SetBool(hashIsIdle, false);
                    break;
            }
            yield return coroutineTime;
        }
    }

    public bool IsViewPlayer()
    {
        bool isView = false;
        RaycastHit hit;

        Vector3 dir      = (playerTr.position - transform.position).normalized;
        Vector3 startPos = transform.position + Vector3.up * rayOffset;

        //레이캐스트를 투사해서 장애물이 있는지 여부를 판단
        if (Physics.Raycast(startPos, dir, out hit, rayRange, layerMask))
        {
            Debug.DrawRay(transform.position, dir, Color.green, 0.5f, true);
            isView = (hit.collider.CompareTag("Player"));
        }
        return isView;
    }

    void StopAttackingDeadPlayer()
    {
        isPlayerDead = true;

        animator.SetBool(hashIsAttack, false);
        animator.SetFloat(hashSpeed, walkSpeed);
        skeletonMovement.agent.speed = walkSpeed;
        skeletonMovement.agent.destination = (transform.position - playerTr.position).normalized;
        skeletonMovement.agent.isStopped = false;
    }

    void Attack()
    {
        var attack = Instantiate(attackPrefab, new Vector3(transform.position.x, transform.position.y + 1.5f, transform.position.z), transform.rotation);
        Rigidbody attackRigidbody = attack.GetComponent<Rigidbody>();       
        attackRigidbody.AddForce(-(attack.transform.position - new Vector3(playerTr.position.x, playerTr.position.y + 1, playerTr.position.z)).normalized * 20, ForceMode.Impulse);
        attack.GetComponent<AudioSource>().volume = DataManagement.DataManager.Instance.SFXVolume;
        Destroy(attack, 6.5f);
    }

    void SkeletonDie()
    {
        if (!EarthRevolution.Instance.IsNightTime)
        {
            playerState.OnPlayerDeath -= StopAttackingDeadPlayer;
            EarthRevolution.Instance.OnSwitchedTime -= SkeletonDie;
            AudioManager.Instance.OnSFXVolumeChanged -= SkeletonVolumeChange;
            AnimalManagement.isSpawnSkeleton = false;
            animator.SetTrigger(hashDead);
            skeletonAudioSource.enabled = false;
            skeletonMovement.Stop();
			isSkeletonDead = true;

            Destroy(gameObject, 10);
        }
    }

    void SkeletonVolumeChange()
    {
        skeletonAudioSource.volume = DataManagement.DataManager.Instance.SFXVolume;
    }

	// 스켈레톤 죽을 때 애니메이션 오류 해결한 코드
    void ChangeBaseOffset()
    {
        skeletonMovement.agent.baseOffset -= 0.5f;
    }

    private void Update()
    {
        if (!isSkeletonDead)
        {
            distFromPlayer = Vector3.SqrMagnitude(playerTr.position - transform.position);

            if (distFromPlayer <= attackDist * attackDist && !isPlayerDead)
            {
                //플레이어와 거리에 장애물 여부를 판단
                if (IsViewPlayer()) //장애물이 없으면 공격모드
                {
                    skeletonMovement.Stop();
                    transform.LookAt(new Vector3(playerTr.position.x, transform.position.y, playerTr.position.z));
                    animator.SetBool(hashIsAttack, true);
                }
                else
                {
                    state = State.TRACE; //장애물이 있으면 추적모드
                }
            }
        }
        if (!isSkeletonDead)
        {
            SkeletonDie();
        }
    }
}
