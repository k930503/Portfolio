using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class AnimalMovement : MonoBehaviour
{
	Vector3 avoidingDestination;        // Avoid상태일때 도망갈 목표지점

    public List<Transform>  wayPoints;  // 순찰 지점들을 저장하기 위한 List 타입 변수
    public int              nextIdx;    // 다음 순찰 지점의 배열의 index

    private float damping = 0.7f;       // 회전할 때의 속도를 조절하는 계수

    public NavMeshAgent agent;
	AnimalState animalState;
    Transform   atThatMomentPlayerTr;

    float           elapsedTime = 0.0f;
	readonly float  durableTime = 4.0f;

	bool isPathPending      = false;    //아직 경로가 준비되지 않았는지 체크
	bool isReceivePlayerTr  = false;

	bool patrolling;
    public bool Patrolling
    {
        get
        {
            return patrolling;
        }
        set
        {
            patrolling = value;
            if (patrolling)
            {
                agent.speed = animalState.walkSpeed;
                damping     = 0.7f;
                MoveWayPoint();
            }
        }
    }

    Vector3 avoidingDirection;
    public Vector3 AvoidingDirection
    {
        get { return avoidingDirection; }
        set
        {
            patrolling          = false;
            avoidingDirection   = value;
            agent.speed         = animalState.runSpeed;
            damping             = 2.5f;
            RunAway(avoidingDirection);
        }
    }
    //추적 대상의 위치를 저장하는 변수
    Vector3 traceTarget;
    public Vector3 TraceTarget
    {
        get { return traceTarget; }
        set
        {
            traceTarget = value;
            agent.speed = animalState.runSpeed;
            damping     = 2.5f;
            ChaseTarget(traceTarget);
        }
    }

	Vector3 walkTarget;
	public Vector3 WalkTarget
	{
		get { return walkTarget; }
		set
		{
			walkTarget  = value;
			agent.speed = animalState.walkSpeed;
			damping     = 2.5f;
			ChaseTarget(walkTarget);
		}
	}
    void Awake()
	{
		agent       = GetComponent<NavMeshAgent>();
		animalState = GetComponent<AnimalState>();

		agent.autoBraking       = false;
		agent.updateRotation    = false;
		agent.speed             = animalState.walkSpeed;
	}

	void Start()
    {
        nextIdx = Random.Range(0, wayPoints.Count);
    }

    // 다음 목적지까지 이동 명령을 내리는 함수
    void MoveWayPoint()
    {
        agent.destination   = wayPoints[nextIdx].position;    // 다음 목적지를 wayPoints 배열에서 추출한 위치로 다음 목적지를 지
        agent.isStopped     = false;                          // 내비게이션 기능을 활성화해서 이동을 시작함

    }

    // 도망치기
    void RunAway(Vector3 direction)
    {
		if(agent.pathPending)
		{
			isPathPending = true;
		}

		if(isPathPending)
		{
			if(!isReceivePlayerTr)
			{
				atThatMomentPlayerTr = GameManager.Instance.Player.transform;
				isReceivePlayerTr    = true;
			}
			agent.destination = transform.position + atThatMomentPlayerTr.right.normalized * 10.0f; // 플레이어와 반대방향으로 도망
		}
		else
		{
			agent.destination = transform.position + direction * 50.0f; // 도망갈길이 막혔을 경우 방향전환
		}		
		agent.isStopped = false;		
	}

    // 플레이어를 추적할 때 이동시키는 함수
    void ChaseTarget(Vector3 pos)
    {
        agent.destination   = pos;
        agent.isStopped     = false;
    }

	//순찰 및 추적을 정지시키는 함수
	public void Stop()
    {
        agent.isStopped = true;
        agent.velocity  = Vector3.zero;  //바로 정지하기 위해 속도를 0으로 설정
        Patrolling      = false;
    }

    void Update()
    {
		elapsedTime += Time.deltaTime;
		if (isPathPending)
		{
			if (elapsedTime > durableTime)
			{
				isPathPending       = false;
				isReceivePlayerTr   = false;
				elapsedTime         = 0.0f;
			}
		}

		//동물이 이동 중일 때만 회전
		if (agent.isStopped == false)
		{
			if (agent.desiredVelocity != Vector3.zero)
			{
				Quaternion rot = Quaternion.LookRotation(agent.desiredVelocity);                            //NavMeshAgent가 가야 할 방향 벡터를 쿼터니언 타입의 각도로 변환                                                                
                transform.rotation = Quaternion.Slerp(transform.rotation, rot, Time.deltaTime * damping);   //보간 함수를 사용해 점진적으로 회전시킴
            }
		}

		//순찰 모드가 아닐 경우 이후 로직을 수행하지 않음
		if (!Patrolling) return;

		//navMeshAgent가 이동하고 있고 목적지에 도착했는지 여부를 계산
		if (agent.velocity.sqrMagnitude > 0.2f * 0.2f
			&& agent.remainingDistance <= 0.5f)
		{
			nextIdx = Random.Range(0, wayPoints.Count);
			
			MoveWayPoint(); // 다음 목적지로 이동 명령을 수행
        }
	}
}
