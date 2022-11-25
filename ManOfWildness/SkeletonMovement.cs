using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class SkeletonMovement : MonoBehaviour
{
    Vector3 avoidingDestination;        // Avoid상태일때 도망갈 목표지점
    float damping = 0.7f;               // 회전할 때의 속도를 조절하는 계수

    public NavMeshAgent agent;
    public SkeletonAI   skeletonAI;

    private void Awake()
    {
        skeletonAI  = GetComponent<SkeletonAI>();
        agent       = GetComponent<NavMeshAgent>();
        agent.autoBraking       = false;
        agent.updateRotation    = false;
        agent.speed = 0;
    }

    public void RunAway(Vector3 avoidingDirection, float avoidingSpeed)
    {
        agent.speed = avoidingSpeed;
        damping = 2.5f;
        agent.destination = transform.position + avoidingDirection * 20.0f;
        agent.isStopped = false;
    }

    //플레이어를 추적할 때 이동시키는 함수
    public void ChaseTarget(Vector3 traceTarget, float chasingSpeed)
    {
        damping = 2.5f;
        agent.speed = chasingSpeed;
        agent.destination = traceTarget;
        agent.isStopped = false;
    }

    //순찰 및 추적을 정지시키는 함수
    public void Stop()
    {
        if (!skeletonAI.isSkeletonDead)
        {
            agent.isStopped = true;
            agent.velocity = Vector3.zero;  //바로 정지하기 위해 속도를 0으로 설정
        }
    }

    void Update()
    {
        if (!skeletonAI.isSkeletonDead)
        {
            //동물이 이동 중일 때만 회전
            if (agent.isStopped == false)
            {
                if (agent.desiredVelocity != Vector3.zero)
                {
                    Quaternion rot = Quaternion.LookRotation(agent.desiredVelocity);                            //NavMeshAgent가 가야 할 방향 벡터를 쿼터니언 타입의 각도로 변환
                    transform.rotation = Quaternion.Slerp(transform.rotation, rot, Time.deltaTime * damping);   //보간 함수를 사용해 점진적으로 회전시킴
                }
            }
        }
    }
}
