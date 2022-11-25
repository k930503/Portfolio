using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class AnimalAI : MonoBehaviour
{
	public enum ChildAttribute
	{
		PARENT,
		CHILD,
		SINGLE
	}
	public enum Type
	{
		AGGRESSIVE,
		HALFAGGRESSIVE,
		AVOIDING,
		INNOCENT
	}
    public enum State
    {
        IDLE,
        PATROL,
        TRACE,
		AVOID,
        ATTACK
    }

    public State            state = State.PATROL;
    public Type             type;
    public ChildAttribute   childAttribute;

    [SerializeField] GameObject[] animalAttack;

	public GameObject childPrefab;
	[HideInInspector]public GameObject mother;
	[HideInInspector]public GameObject child;
    [HideInInspector]public GameObject generatePoint = null;

    bool isPlayerDead = false;
    [HideInInspector] public bool isAnimalDead      = false;
    [HideInInspector] public bool isMotherDead      = false;
    [HideInInspector] public bool isChildDead       = false;
    [HideInInspector] public bool isWayPointReset   = true;

	float distFromPlayer;
	float traceDist     = 10.0f;    //trace모드로 전환하기위해 측정
	float avoidingDist  = 35.0f;    //avoiding모드로 전환하기위해 측정
	float stoppingDist  = 5.0f;     //어미에게 더이상 다가오지 못하게 하기위해서 측정
	float minimumDist   = 15.0f;    //어미와 최소간격 유지
	float destroyDist   = 250.0f;   //플레이어와 거리가 멀어지면 destroy

    public float attackDist;

    //코루틴에서 사용할 지연시간 변수
    WaitForSeconds coroutineTime;
    WaitForSeconds soundDelayTime;

    Transform       playerTr;
    Animator        animator;
    AnimalMovement  animalMovement;
    AnimalFOV       animalFOV;      //시야각 및 detect 반경을 제어하는 animalFOV 클래스를 저장할 변수
    AnimalHpBar     animalHpBar;
	AnimalState     animalState;

    public AudioClip[] clip = null;
    public AudioSource audioSource;

    readonly int hashAttack     = Animator.StringToHash("Attack");
    readonly int hashDead       = Animator.StringToHash("Dead");
    readonly int hashRun        = Animator.StringToHash("Run");
    readonly int hashDamage     = Animator.StringToHash("Damage");
    readonly int hashOrdinary   = Animator.StringToHash("Ordinary");
    readonly int hashIdle0Walk1 = Animator.StringToHash("Idle0Walk1");

    float elapsedTime = 0;
    float durableTime = 5.0f;

    int idle0Walk12 = 0;    // 0,1 값이 바뀌면서 애니메이터 상태변환

    void Awake()
    {
        animator        = GetComponent<Animator>();
        animalMovement  = GetComponent<AnimalMovement>();
        animalFOV       = GetComponent<AnimalFOV>();  
        animalHpBar     = GetComponent<AnimalHpBar>();
		animalState     = GetComponent<AnimalState>();
        audioSource     = GetComponent<AudioSource>();

        //코루틴의 지연시간 생성
		coroutineTime   = new WaitForSeconds(0.3f);
        soundDelayTime  = new WaitForSeconds(10.0f);
    }

    void OnEnable()
    {
        AudioVolumeChange();
        AudioManager.Instance.OnSFXVolumeChanged += AudioVolumeChange;
    }

    void OnDestroy()
    {
        if(AudioManager.Instance != null)
            AudioManager.Instance.OnSFXVolumeChanged -= AudioVolumeChange;
    }

    void AudioVolumeChange()
    {
        audioSource.volume = DataManagement.DataManager.Instance.SFXVolume;
    }

    void Start()
    {
        var player = GameManager.Instance.Player;

        if(player != null)
        {
            PlayerState playerState     =   player.GetComponent<PlayerState>();
            playerState.OnPlayerDeath   +=  StopAttackingDeadPlayer;
            playerTr                    =   player.transform;
        }

		if(childAttribute == ChildAttribute.PARENT)
		{
			GameObject childAnimal = Instantiate(childPrefab, 
                                                   new Vector3(transform.position.x + 3, transform.position.y + 1, transform.position.z + 5), 
                                                   transform.rotation);

			childAnimal.GetComponent<AnimalAI>().mother = gameObject;
			child = childAnimal;
		}

        StartCoroutine(SoundManager());
		StartCoroutine(CheckState());

		if (type == Type.INNOCENT)
		{
			StartCoroutine(ChildAction());
		}
		else
		{
			StartCoroutine(Action());
		}
	}

    IEnumerator CheckState()
    {
		state = State.PATROL;

		yield return new WaitForSeconds(1.0f);  //오브젝트 풀에 생성 시 다른 스크립트의 초기화를 위해 대기

        //동물이 사망하기 전까지 도는 무한루프
        while (!isAnimalDead)
		{
            //심리스방식 도입시 필요한 region
            #region
            /*if (generatePoint != null) 
            {
                if (Vector3.SqrMagnitude(generatePoint.transform.position - transform.position) > renounceDist * renounceDist)
                {
                    state = State.PATROL;
                    yield return coroutineTime;
                    continue;
                }
            }*/
            #endregion

            switch (type)
            {
                case Type.AGGRESSIVE:

                    //쫓아감
                    //추적 반경 및 시야각에 들어왔는지를 판단
                    if (animalFOV.IsDetectPlayer() && !isPlayerDead || state == State.TRACE)
                    {
                        if (animalFOV.IsViewPlayer())
                        {
                            state = State.TRACE;
                        }
                        else
                        {
                            state = State.PATROL;
                        }
                    }
                    //순찰
                    else
                    {
                        state = State.PATROL;
                    }
                    break;





                case Type.HALFAGGRESSIVE:

                    //회피 사정거리 이내인 경우
                    if (animalFOV.IsDetectPlayer() && state != State.TRACE && state != State.ATTACK && !isPlayerDead)
                    {
                        while (distFromPlayer <= avoidingDist * avoidingDist && !isAnimalDead)
                        {
                            state = State.AVOID;

                            yield return null;
                        }
                    }
                    //추적 반경 및 시야각에 들어왔는지를 판단
                    else if (animalFOV.IsDetectPlayer() && !isPlayerDead || state == State.TRACE)
                    {
                        if (animalFOV.IsViewPlayer()) //장애물이 없으면 공격모드
                        {
                            state = State.TRACE;
                        }
                        else
                        {
                            state = State.PATROL;
                        }
                    }
                    else
                    {
                        state = State.PATROL;
                    }
                    break;





                case Type.AVOIDING:

                    //회피 사정거리 이내인 경우
                    if (animalFOV.IsDetectPlayer())
                    {
                        while (distFromPlayer <= avoidingDist * avoidingDist && !isAnimalDead)
                        {
                            state = State.AVOID;

                            yield return null;
                        }
                    }
                    else if (state == State.AVOID)
                    {
                        float originDist = distFromPlayer;

                        while (distFromPlayer <= originDist + avoidingDist * avoidingDist && !isAnimalDead)
                        {
                            yield return null;
                        }
                        state = State.PATROL;
                    }
                    else
                    {
                        state = State.PATROL;
                    }
                    break;





                case Type.INNOCENT:

                    if (isMotherDead)
                    {
                        type = Type.AVOIDING;
                        StartCoroutine(Action());

                        continue;
                    }

                    if (!isMotherDead)
                    {
                        float distFromMother = Vector3.SqrMagnitude(mother.transform.position - transform.position);

                        if (distFromMother > minimumDist * minimumDist)
                        {
                            state = State.TRACE;
                        }
                        else if (distFromMother > stoppingDist * stoppingDist)
                        {
                            state = State.PATROL;
                        }
                        else
                        {
                            state = State.IDLE;
                        }
                    }
                    break;
            }

            yield return coroutineTime;
        }		   
	}

    IEnumerator Action()
    {
		//오브젝트 풀에 생성 시 다른 스크립트의 초기화를 위해 대기
		yield return new WaitForSeconds(1.0f);

		while (!isAnimalDead)
		{
			switch (state)
			{
				case State.PATROL:

					animator.SetTrigger(hashOrdinary);
					if (idle0Walk12 == 0)
					{
						animalMovement.Stop();
						animator.SetFloat(hashIdle0Walk1, 0);
					}
					else
					{
						animalMovement.Patrolling = true;
						animator.SetFloat(hashIdle0Walk1, 1);
					}
					break;

				case State.TRACE:

					animalMovement.TraceTarget = playerTr.position;
					animator.SetTrigger(hashRun);
					break;

				case State.AVOID:
                					
					animalMovement.AvoidingDirection = (transform.position - playerTr.position).normalized;
					animator.SetTrigger(hashRun);
					isWayPointReset = true;
					break;
			}
			yield return coroutineTime;
		}
    }

	IEnumerator ChildAction()
	{
		AnimalAI motherAnimalAI = mother.GetComponent<AnimalAI>();

		while (!motherAnimalAI.isAnimalDead && !isAnimalDead)
		{
			switch (state)
			{
				case State.PATROL:

					animalMovement.WalkTarget = mother.transform.position;
					animator.SetTrigger(hashOrdinary);
					animator.SetFloat(hashIdle0Walk1, 1);
					break;

				case State.TRACE:

					animalMovement.TraceTarget = mother.transform.position;
					animator.SetTrigger(hashRun);
					isWayPointReset = false;
					break;

				case State.IDLE:

					animalMovement.Stop();
					animator.SetTrigger(hashOrdinary);
					animator.SetFloat(hashIdle0Walk1, 0);
					break;
			}
			yield return null;
		}
	}

    IEnumerator SoundManager()
    {
        while(!isAnimalDead)
        {        
            if (clip.Length > 0)
            {
                audioSource.PlayOneShot(clip[Random.Range(1, clip.Length)]);
            }

            yield return soundDelayTime;
        }
    }

    void StopAttackingDeadPlayer()
    {
        state           = State.PATROL;
        isPlayerDead    = true;
    }

    public void ItemDrop()
    {
        int dropCount = Random.Range(animalState.minimumItemDropCount, animalState.maximumItemDropCount + 1);
        for(int i = 0; i < dropCount; i++)
        {
            GameObject  item            = Instantiate(GameManager.Instance.meatPickupPrefab);
            Rigidbody   itemRigidBody   = item.GetComponent<Rigidbody>();

            item.transform.position = gameObject.transform.position;
            itemRigidBody.AddForce(new Vector3(Random.Range(-2,3), 10, Random.Range(-2, 3)), ForceMode.Impulse);
        }
    }

    void SetActiveAttackObj()
    {
        for (int i = 0; i < animalAttack.Length; i++)
        {
            animalAttack[i].SetActive(true);
        }
    }

    void SetDeactiveAttackObj()
    {
        for (int i = 0; i < animalAttack.Length; i++)
        {
            animalAttack[i].SetActive(false);
        }
    }
  
	private void Update()
    {
		distFromPlayer = Vector3.SqrMagnitude(playerTr.position - transform.position);

        if (distFromPlayer > destroyDist * destroyDist)
        {
            switch (childAttribute)
            {
                case ChildAttribute.PARENT:

                    if (!isChildDead)
                    {
                        child.GetComponent<AnimalAI>().isMotherDead = true;
                    }
                    generatePoint.GetComponent<AnimalManagement>().isSpawn = false;
                    break;

                case ChildAttribute.SINGLE:

                    generatePoint.GetComponent<AnimalManagement>().isSpawn = false;
                    break;

                case ChildAttribute.CHILD:

                    if (!isMotherDead)
                    {
                        mother.GetComponent<AnimalAI>().isChildDead = true;
                    }
                    break;
            }

            if (animalHpBar.isActiveHpBar)
            {
                Destroy(animalHpBar.hpBar);
            }
            isAnimalDead = true;
            Destroy(gameObject);
        }



        if (state == State.PATROL)
        {
            elapsedTime += Time.deltaTime;

            if (elapsedTime > durableTime)
            {              
				idle0Walk12 = Random.Range(0, 3);
                elapsedTime = 0;
            }
        }

		if (type == Type.AGGRESSIVE || type == Type.HALFAGGRESSIVE)
		{
			if (!isPlayerDead && !isAnimalDead && distFromPlayer <= attackDist * attackDist && animalFOV.IsDetectPlayer())
			{
				animalMovement.Stop();
				transform.LookAt(new Vector3(playerTr.position.x, transform.position.y, playerTr.position.z));
				animator.SetTrigger(hashAttack);
			}
		}
	}
}
