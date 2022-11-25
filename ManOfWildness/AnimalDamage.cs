using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class AnimalDamage : MonoBehaviour {

	AnimalAI        animalAI;
    AnimalState     animalState;
    AnimalMovement  animalMovement;
    AnimalHpBar     animalHpBar;
    Animator        animator;

	float initHp;

    readonly int hashDamage = Animator.StringToHash("Damage");
    readonly int hashDead   = Animator.StringToHash("Dead");
	readonly int hashExit   = Animator.StringToHash("Exit");

	void Awake()
    {
        animator        = GetComponent<Animator>();
        animalAI        = GetComponent<AnimalAI>();
        animalState     = GetComponent<AnimalState>();
        animalMovement  = GetComponent<AnimalMovement>();
        animalHpBar     = GetComponent<AnimalHpBar>();
    }

    void Start ()
    {
        initHp = animalState.hp;     
	}

    void OnTriggerEnter(Collider other)
    {
		if (!animalAI.isAnimalDead)
		{
			if (other.gameObject.CompareTag("PlayerAttack"))
			{
				ShowBloodEffect(other);
				animalState.hp -= other.gameObject.GetComponent<WeaponCondition>().damage;

                //HPBar활성화
				if (!animalHpBar.isActiveHpBar)
				{
					animalHpBar.SetHpBar();
				}
				else
				{
					animalHpBar.elapsedTime = 0;
				}

				//피해를 입고 죽지않았을 경우 동물별 상태변화 
				if (animalState.hp > 0)
				{
					animalHpBar.hpBar.GetComponentsInChildren<Image>()[1].fillAmount = animalState.hp / initHp;
					if (animalAI.type == AnimalAI.Type.AGGRESSIVE || animalAI.type == AnimalAI.Type.HALFAGGRESSIVE)
					{
						animalAI.state = AnimalAI.State.TRACE;
					}
					else if (animalAI.type == AnimalAI.Type.AVOIDING)
					{
						animalAI.state = AnimalAI.State.AVOID;
					}
					else if (animalAI.childAttribute == AnimalAI.ChildAttribute.CHILD)
					{
						if (!animalAI.isMotherDead)
						{
							if (animalAI.mother.GetComponent<AnimalAI>().type == AnimalAI.Type.AGGRESSIVE || animalAI.mother.GetComponent<AnimalAI>().type == AnimalAI.Type.HALFAGGRESSIVE)
							{
								animalAI.mother.GetComponent<AnimalAI>().state = AnimalAI.State.TRACE;
							}
							else if (animalAI.mother.GetComponent<AnimalAI>().type == AnimalAI.Type.AVOIDING)
							{
								animalAI.mother.GetComponent<AnimalAI>().state = AnimalAI.State.AVOID;
							}
						}
					}

					animalMovement.Stop();
					animator.SetTrigger(hashDamage);
					animalAI.audioSource.PlayOneShot(animalAI.clip[0]);
				}
				//피해를 입고 죽은 경우
				else
				{
					animalAI.isAnimalDead = true;

					animalMovement.Stop();
					animator.SetTrigger(hashDead);
					animator.SetTrigger(hashExit);
					animalAI.audioSource.PlayOneShot(animalAI.clip[0]);
					animalAI.ItemDrop();

                    //어미일 경우 새끼한테 본인의 죽음을 알림
					if (animalAI.childAttribute == AnimalAI.ChildAttribute.PARENT)
					{
						if (!animalAI.isChildDead)
						{
							animalAI.child.GetComponent<AnimalAI>().isMotherDead = true;
						}
						animalAI.generatePoint.GetComponent<AnimalManagement>().isSpawn = false;    //스폰포인트에서 새로 동물을 생성할 수 있도록
					}
                    //새끼일 경우 어미한테 본인의 죽음을 알리고 어미 성향에 따라 상태변화 
					else if (animalAI.childAttribute == AnimalAI.ChildAttribute.CHILD)
					{
						if (!animalAI.isMotherDead)
						{
							animalAI.mother.GetComponent<AnimalAI>().isChildDead = true;

							if (animalAI.mother.GetComponent<AnimalAI>().type == AnimalAI.Type.AGGRESSIVE ||
                                animalAI.mother.GetComponent<AnimalAI>().type == AnimalAI.Type.HALFAGGRESSIVE)
							{
								animalAI.mother.GetComponent<AnimalAI>().state = AnimalAI.State.TRACE;
							}
							else if (animalAI.mother.GetComponent<AnimalAI>().type == AnimalAI.Type.AVOIDING)
							{
								animalAI.mother.GetComponent<AnimalAI>().state = AnimalAI.State.AVOID;
							}
						}
					}

					if (animalHpBar.isActiveHpBar)
					{
						Destroy(animalHpBar.hpBar);
					}
                    animalAI.StopAllCoroutines();
					Destroy(gameObject, 10);
				}
			}
		}
    }

    // 혈흔 효과를 생성하는 함수
    void ShowBloodEffect(Collider collider)
    {
        Vector3 pos = collider.transform.position;  // 화살이 충돌한 지점 계산
        Vector3 normal = collider.transform.forward;    // 화살이 충돌했을 때의 법선 벡터
        Quaternion rotation = Quaternion.FromToRotation(-Vector3.forward, normal);  // 화살 충돌시 방향 벡터에 따른 회전 정보 계산
        GameObject blood = Instantiate(GameManager.Instance.animalBloodEffect, pos, rotation);
        Destroy(blood, 1.0f);
    }
}
