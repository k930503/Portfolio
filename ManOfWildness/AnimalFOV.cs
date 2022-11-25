using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AnimalFOV : MonoBehaviour {

	float rayRange = 150.0f;
    [Range(0, 360)]
	float offset = 1.5f;    //기준축에서 위쪽으로

    int playerLayer;
    int obstacleLayer;
    int layerMask;

    AnimalState     animalstate;
	PlayerMovement  playerMovement;
    Transform       playerTr;

    void Start () {

		var player = GameManager.Instance.Player;
		if (player != null)
		{
			PlayerState playerState = player.GetComponent<PlayerState>();

			playerTr = player.GetComponent<Transform>();
			playerMovement = player.GetComponent<PlayerMovement>();
		}

		animalstate = GetComponent<AnimalState>();

        //레이어 마스크 값 계산
        playerLayer = LayerMask.NameToLayer("Player");
        obstacleLayer = LayerMask.NameToLayer("Obstacle");
        layerMask = 1 << playerLayer | 1 << obstacleLayer;
	}
	
    //주어진 각도에 의해 원주 위의 점을 좌푯값을 계산하는 함수
    public Vector3 CirclePoint(float angle)
    {
        angle += transform.eulerAngles.y;   //로컬 좌표계 기준으로 설정하기 위해 적 캐릭터의 Y 회전값을 더함
        return new Vector3(Mathf.Sin(angle * Mathf.Deg2Rad)
            , 0
            , Mathf.Cos(angle * Mathf.Deg2Rad));
    }

    public bool IsDetectPlayer()
    {
        bool isDetect = false;
		Collider[] colls;

        //플레이어가 살금살금 다가오면 동물의 시야가 좁아짐
		if (playerMovement.IsSneaking)
		{
			colls = Physics.OverlapSphere(transform.position, animalstate.viewRange * 0.4f, 1 << playerLayer);
		}
		else
		{
			colls = Physics.OverlapSphere(transform.position, animalstate.viewRange, 1 << playerLayer);
		}

		//배열의 개수가 1일 때 주인공이 범위 안에 있다고 판단
		if (colls.Length > 0)
        {
            Vector3 dir = (playerTr.position - transform.position).normalized;  //동물과 주인공 사이의 방향 벡터를 계산

            //동물의 시야각에 들어왔는지 판단
            if (Vector3.Angle(transform.forward, dir) < animalstate.viewAngle * 0.5f)
            {
				isDetect = true;
            }
        }
        return isDetect;
    }

    public bool IsViewPlayer()
    {
        bool isView = false;
        RaycastHit hit;

        Vector3 dir = (playerTr.position - transform.position).normalized;  //동물과 주인공 사이의 방향 벡터를 계산                                                                          
        Vector3 startPos = transform.position + Vector3.up * offset;        //todo 플레이어랑 동물 사이 거리 계산하는 플롯변수

        //레이캐스트를 투사해서 장애물이 있는지 여부를 판단                                                         
        if (Physics.Raycast(startPos, dir, out hit, rayRange, layerMask))
        {
			Debug.DrawRay(transform.position, dir, Color.green, 0.5f, true);
			isView = (hit.collider.CompareTag("Player"));
        }
        return isView;
    }
}
