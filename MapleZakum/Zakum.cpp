#include "Zakum.h"
#include "Texture.h"
#include "SDLFramework.h"
#include "GameManager.h"
#include "Transform.h"
#include "State.h"
#include "FirePillar.h"
#include "Thunder.h"
#include "Arm.h"
#include "Body.h"
#include "RectangleCollider.h"
#include <random>
#include <iostream>

int GenerateRandom(int min, int max)
{
	//< 1단계. 시드 설정
	random_device rn;
	mt19937_64 rnd(rn());

	//< 2단계. 분포 설정 ( 정수 )
	uniform_int_distribution<int> range(min, max);

	//< 3단계. 값 추출
	return range(rnd);
}

Zakum::Zakum()
{
	frameRate = 5.0f;
	elapsedTime = 0.0f;

	//팔 생성
	arm[0] = new SDLGameObject("Arm1", 20.0, 16);
	arm[1] = new SDLGameObject("Arm2", 40.0, 11);
	arm[2] = new SDLGameObject("Arm3", 60.0, 13);
	arm[3] = new SDLGameObject("Arm4", 80.0, 19);
	arm[4] = new SDLGameObject("Arm5", 90.0, 14);
	arm[5] = new SDLGameObject("Arm6", 100.0, 18);
	arm[6] = new SDLGameObject("Arm7", 120.0, 11);
	arm[7] = new SDLGameObject("Arm8", 140.0, 16);

	for (int i = 0; i < 8; i++)
	{
		arm[i]->AddComponent<Arm>();
		arm[i]->AddComponent<Texture>();
		arm[i]->AddComponent<State>();

		State* state = arm[i]->GetComponent<State>();
		state->SetHp(400);
		arm[i]->AddComponent<RectangleCollider>();
		RectangleCollider* collider = arm[i]->GetComponent<RectangleCollider>();
		collider->colliderType = ZakumArmType;
		SDLFramework::Instance()->collideObj.insert(pair<string, SDLGameObject*>(arm[i]->name, arm[i]));
		SDLFramework::Instance()->AddCollideGameObject(arm[i]);
		
		Texture* texture = arm[i]->GetComponent<Texture>();
		texture->SetTexture(SDLFramework::Instance()->textures[i + 1]);
		texture->SetHorizonCount(1);
		texture->SetVerticalCount(1);
		texture->SetAnimationActive(true);
			
		switch (i) 
		{
			case 0:
				arm[i]->transform->SetPosition(400, 100);
				arm[i]->transform->SetWidth(155);
				arm[i]->transform->SetHeight(228);
				arm[i]->transform->SetCenterPoint(125, 177);
				break;
			case 1:
				arm[i]->transform->SetPosition(600, 100);
				arm[i]->transform->SetWidth(160);
				arm[i]->transform->SetHeight(224);
				arm[i]->transform->SetCenterPoint(12, 201);
				break;
			case 2:
				arm[i]->transform->SetPosition(310, 170);
				arm[i]->transform->SetWidth(229);
				arm[i]->transform->SetHeight(165);
				arm[i]->transform->SetCenterPoint(225, 138);
				break;
			case 3:
				arm[i]->transform->SetPosition(600, 170);
				arm[i]->transform->SetWidth(240);
				arm[i]->transform->SetHeight(184);
				arm[i]->transform->SetCenterPoint(0, 154);
				break;
			case 4:
				arm[i]->transform->SetPosition(285, 300);
				arm[i]->transform->SetWidth(250);
				arm[i]->transform->SetHeight(111);
				arm[i]->transform->SetCenterPoint(235, 34);
				break;
			case 5:
				arm[i]->transform->SetPosition(600, 250);
				arm[i]->transform->SetWidth(260);
				arm[i]->transform->SetHeight(186);
				arm[i]->transform->SetCenterPoint(9, 128);
				break;
			case 6:
				arm[i]->transform->SetPosition(280, 370);
				arm[i]->transform->SetWidth(249);
				arm[i]->transform->SetHeight(145);
				arm[i]->transform->SetCenterPoint(228, 23);
				break;
			case 7:
				arm[i]->transform->SetPosition(620, 380);
				arm[i]->transform->SetWidth(264);
				arm[i]->transform->SetHeight(122);
				arm[i]->transform->SetCenterPoint(16, 31);
				break;
		}
	}

	//몸체 생성
	body = new SDLGameObject("Body");
	body->AddComponent<Body>();
	body->AddComponent<Texture>();
	body->AddComponent<State>();
	State* state = body->GetComponent<State>();
	state->SetHp(1280);
	Texture* texture = body->GetComponent<Texture>();
	texture->SetTexture(SDLFramework::Instance()->textures[9]);
	texture->SetFrameRate(0.13f);
	texture->SetHorizonCount(4);
	texture->SetVerticalCount(2);
	texture->SetBlendMode(SDL_BLENDMODE_BLEND);
	texture->SetAlpha(0xff);
	texture->SetAnimationActive(true);
	body->transform->SetPosition(360, 125);
	body->transform->SetWidth(400);
	body->transform->SetHeight(400);

	//불기둥 생성
	for (int i = 0; i < 7; i++)
	{
		string firePillarObjName = "firePillarCue" + to_string(i);
		firePillar[i] = new SDLGameObject(firePillarObjName.c_str(), true);
		string areaObjectName = "AreaPreview" + to_string(i);
		string fireObjectName = "DropFire" + to_string(i);
		string destroyObjectName = "destroyFire" + to_string(i);

		firePillar[i]->AddComponent<FirePillar>();
		FirePillar* fp = firePillar[i]->GetComponent<FirePillar>();
		fp->areaPreview = new SDLGameObject(areaObjectName.c_str(), fp->areaPreview);
		fp->areaPreview->AddComponent<Texture>();
		texture = fp->areaPreview->GetComponent<Texture>();
		texture->SetTexture(SDLFramework::Instance()->textures[10]);
		texture->SetFrameRate(0.13f);
		texture->SetHorizonCount(6);
		texture->SetVerticalCount(1);
		texture->SetBlendMode(SDL_BLENDMODE_BLEND);
		texture->SetAlpha(0xff);
		texture->SetAnimationActive(true);
		fp->areaPreview->transform->SetWidth(105);
		fp->areaPreview->transform->SetHeight(262);

		fp->dropFire = new SDLGameObject(fireObjectName.c_str(), fp->dropFire);
		fp->dropFire->AddComponent<RectangleCollider>();
		RectangleCollider* collider = fp->dropFire->GetComponent<RectangleCollider>();
		collider->colliderType = ZakumSkillType;
		SDLFramework::Instance()->collideObj.insert(pair<string, SDLGameObject*>(fireObjectName.c_str(), fp->dropFire));
		SDLFramework::Instance()->AddCollideGameObject(fp->dropFire);
		fp->dropFire->AddComponent<Texture>();
		texture = fp->dropFire->GetComponent<Texture>();
		texture->SetTexture(SDLFramework::Instance()->textures[11]);
		texture->SetHorizonCount(1);
		texture->SetVerticalCount(1);
		texture->SetBlendMode(SDL_BLENDMODE_BLEND);
		texture->SetAlpha(0xFF);
		texture->SetAnimationActive(true);
		fp->dropFire->transform->SetWidth(75);
		fp->dropFire->transform->SetHeight(210);

		fp->destroyFire = new SDLGameObject(destroyObjectName.c_str(), fp->destroyFire);
		fp->destroyFire->AddComponent<Texture>();
		texture = fp->destroyFire->GetComponent<Texture>();
		texture->SetTexture(SDLFramework::Instance()->textures[12]);
		texture->SetFrameRate(0.13f);
		texture->SetHorizonCount(7);
		texture->SetVerticalCount(1);
		texture->SetBlendMode(SDL_BLENDMODE_BLEND);
		texture->SetAlpha(0xff);
		texture->SetAnimationActive(true);
		fp->destroyFire->transform->SetWidth(105);
		fp->destroyFire->transform->SetHeight(262);
		firePillar[i]->active = false;
	}

	//썬더 생성
	for (int i = 0; i < 7; i++)
	{
		string thunderObjName = "thunder" + to_string(i);
		thunder[i] = new SDLGameObject(thunderObjName.c_str(), false);
		thunder[i]->AddComponent<RectangleCollider>();
		RectangleCollider* collider = thunder[i]->GetComponent<RectangleCollider>();
		collider->colliderType = ZakumSkillType;
		SDLFramework::Instance()->collideObj.insert(pair<string, SDLGameObject*>(thunderObjName.c_str(), thunder[i]));
		SDLFramework::Instance()->AddCollideGameObject(thunder[i]);
		thunder[i]->AddComponent<Thunder>();
		thunder[i]->AddComponent<Texture>();
		texture = thunder[i]->GetComponent<Texture>();
		texture->SetTexture(SDLFramework::Instance()->textures[13]);
		texture->SetFrameRate(0.13f);
		texture->SetHorizonCount(5);
		texture->SetVerticalCount(1);
		texture->SetBlendMode(SDL_BLENDMODE_BLEND);
		texture->SetAlpha(0xff);
		texture->SetAnimationActive(true);
		thunder[i]->transform->SetWidth(105);
		thunder[i]->transform->SetHeight(528);
	}
}

Zakum::~Zakum()
{
}

void Zakum::Update(float deltaTime) 
{
	for (int i = 0; i < 8; i++)
	{
		arm[i]->Update(deltaTime);
	}
	if (armDieCheck) 
	{
		if (!(arm[0]->active || arm[1]->active || arm[2]->active || arm[3]->active || arm[4]->active || arm[5]->active || arm[6]->active || arm[7]->active)) 
		{
			body->AddComponent<RectangleCollider>();
			RectangleCollider* collider = body->GetComponent<RectangleCollider>();
			collider->colliderType = ZakumBodytype;
			SDLFramework::Instance()->collideObj.insert(pair<string, SDLGameObject*>(body->name, body));
			SDLFramework::Instance()->AddCollideGameObject(body);
			armDieCheck = false;
		}
	}
	// 팔이 다 떨어진 몸체
	if (body2ChangeCheck)
	{
		if (body->GetComponent<State>()->GetHp() < 640) {
			Texture* texture = body->GetComponent<Texture>();
			texture->SetTexture(SDLFramework::Instance()->textures[14]);

			body2ChangeCheck = false;
		}
	}
	// 체력의 반이상 소모한 몸체
	if (body3ChangeCheck)
	{
		if (body->GetComponent<State>()->GetHp() < 100) {
			Texture* texture = body->GetComponent<Texture>();
			texture->SetTexture(SDLFramework::Instance()->textures[14]);

			body3ChangeCheck = false;
		}
	}
	if (body3DieCheck)
	{
		if (body->GetComponent<State>()->GetHp() <= 0) {
			Texture* texture = body->GetComponent<Texture>();
			texture->SetTexture(SDLFramework::Instance()->textures[15]);
			texture->SetFrameRate(0.13f);
			texture->SetHorizonCount(8);
			texture->SetVerticalCount(2);
			body->transform->SetPosition(355,175);
			body->transform->SetWidth(400);
			body->transform->SetHeight(500);

			body3DieCheck = false;
		}
	}
	body->Update(deltaTime);


	for (int j = 0; j < 7; j++)
	{
		if (firePillar[j]->active)
			firePillar[j]->Update(deltaTime);
	}

	for (int j = 0; j < 7; j++)
	{
		if (thunder[j]->active)
			thunder[j]->Update(deltaTime);
	}
	
	// 불기둥, 번개 공격 로직
	elapsedTime += deltaTime;
	if (elapsedTime > frameRate)
	{
		int randomArr[5] = { 0, };
		int temp = 0;
		int attackPattern = 0;
		bool redundancyCheck = false;


		attackPattern = GenerateRandom(1, 2);	// 1 = 불기둥, 2 = 번개
		cout << attackPattern << endl;

		// 타격을 입힐 5개 지역을 중복되지않게 고르기
		for (int i = 0; i < 5; i++) {

			redundancyCheck = false;

			while (!redundancyCheck) {
				temp = GenerateRandom(1, 12);
				for (int j = 0; j <= i; j++) {
					if (randomArr[j] != temp) {
						redundancyCheck = true;	
					}
					else
					{
						redundancyCheck = false;
						break;
					}
				}
			}
			randomArr[i] = temp;
			cout << " randomArr[i] : " << randomArr[i] << endl;

			FirePillar* fp = firePillar[i]->GetComponent<FirePillar>();
				
			if (randomArr[i] == 1) {
				fp->SetPosition(0, 264);
				thunder[i]->transform->SetPosition(0, 0);
				thunder[i]->GetComponent<Texture>()->SetFrameCount(0);
			}
			
			else {
				fp->SetPosition(randomArr[i] * 105, 264);
				thunder[i]->transform->SetPosition(randomArr[i] * 105, 0);
				thunder[i]->GetComponent<Texture>()->SetFrameCount(0);
			}
			
			switch (attackPattern)
			{
			case 1:
					fp->Activate();
					break;
			case 2:
					for (int i = 0; i < 7; i++)
					{
						thunder[i]->active = true;
					}
					break;
			}	
		}
		elapsedTime = 0.0f;
	}
}

void Zakum::Render()
{
	for (int i = 0; i < 8; i++)
	{
		if (arm[i]->active)
			arm[i]->Render();
	}
	if (body->active)
		body->Render();

	for (int i = 0; i < 7; i++)
	{
		if(firePillar[i]->active)
			firePillar[i]->Render();
	}

	for (int i = 0; i < 7; i++)
	{
		if (thunder[i]->active)
			thunder[i]->Render();
	}
}
