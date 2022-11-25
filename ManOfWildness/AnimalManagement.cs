using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AnimalManagement : MonoBehaviour {

	public bool         isSpawn = false;    //스폰이 되있는경우 스폰하지않도록 체크(동물)
    public static bool  isSpawnSkeleton = false;    //수 많은 스폰포인트 중에서 일정거리 이상 떨어진 단 하나의 스폰포인트에서만 생성시키기 위함

	public GameObject   animalPrefab;

	Transform   playerTr;
	PointGizmo  pointGizmo;

    readonly float enterDist                     = 200.0f;  //플레이어와 스폰포인트의 거리 재기
    readonly float possibleSpawnSkeletonDistance = 400.0f;  //너무 가까이 있는 스폰포인트는 해골전사 생성후보에서 제외
    float distanceFromPlayer;

    private void Start()
    {
		pointGizmo  = GetComponent<PointGizmo>();
		playerTr    = GameManager.Instance.Player.transform;
        EarthRevolution.Instance.OnSwitchedTime += SpawnSkeleton;
    }

    //동물 스폰
	public void SpawnAnimal()
	{
		var obj = Instantiate(animalPrefab, transform.position, transform.rotation);
		obj.GetComponent<AnimalAI>().generatePoint = gameObject;
		isSpawn = true;
	}

    //델리게이트를 통해 밤을 체크하고 해골전사 생성
    public void SpawnSkeleton()
    {
        if(EarthRevolution.Instance.IsNightTime && !isSpawnSkeleton && pointGizmo.habitat != PointGizmo.Habitat.Water)
        {
			if (distanceFromPlayer < possibleSpawnSkeletonDistance * possibleSpawnSkeletonDistance)
			{
				var obj = Instantiate(GameManager.Instance.skeletonPrefab, transform.position, transform.rotation);
				isSpawnSkeleton = true;
			}
        }
    }

    //주변에 플레이어가 있는지 체크후 생성
    void DetectPlayer()
	{
        distanceFromPlayer = Vector3.SqrMagnitude(playerTr.position - transform.position);

		if (distanceFromPlayer < enterDist * enterDist)
		{
            if (!isSpawn)
            {
                SpawnAnimal();
            }
		}
	}

	private void Update()
	{
		DetectPlayer();
	}
}
