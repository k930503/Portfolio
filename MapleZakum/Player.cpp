#include "Player.h"
#include "Transform.h"
#include "KeyboardTest.h"
#include "RectangleCollider.h"
#include "CircleCollider.h"
#include "SDLFramework.h"
#include "Texture.h"
#include "State.h"
#include "LeftDart.h"
#include "RightDart.h"
#include "GameManager.h"
#include <iostream>

using namespace std;

Player::Player()
{
	elapsedTime		= 0.0f;
	frameRate		= 0.08f;
	duration		= 0.017f;
	leftDartCnt		= 0;
	rightDartCnt	= 0;
	attackState		= 0;
	directionState	= 1;

	//여유있게 수리검 18개씩 만들어놓기
	for (int i = 0; i < 18; i++)
	{
		string dartObjName = "leftDart" + to_string(i);
		leftDart[i] = new SDLGameObject(dartObjName.c_str(), false);
		leftDart[i]->AddComponent<LeftDart>();
		leftDart[i]->AddComponent<Texture>();
		leftDart[i]->AddComponent<RectangleCollider>();

		RectangleCollider* collider = leftDart[i]->GetComponent<RectangleCollider>();
		collider->colliderType = DartType;

		SDLFramework::Instance()->AddCollideGameObject(leftDart[i]);

		Texture* texture = leftDart[i]->GetComponent<Texture>();
		texture->SetTexture(SDLFramework::Instance()->textures[20]);
		texture->SetFrameRate(0.13f);
		texture->SetHorizonCount(1);
		texture->SetVerticalCount(1);
		texture->SetBlendMode(SDL_BLENDMODE_BLEND);
		texture->SetAlpha(0xff);
		texture->SetAnimationActive(true);
		leftDart[i]->transform->SetWidth(50);
		leftDart[i]->transform->SetHeight(20);
	}

	for (int i = 0; i < 18; i++)
	{
		string dartObjName = "rightDart" + to_string(i);
		rightDart[i] = new SDLGameObject(dartObjName.c_str(), false);
		rightDart[i]->AddComponent<Texture>();
		rightDart[i]->AddComponent<RectangleCollider>();

		RectangleCollider* collider = rightDart[i]->GetComponent<RectangleCollider>();
		collider->colliderType = DartType;

		SDLFramework::Instance()->AddCollideGameObject(rightDart[i]);

		rightDart[i]->AddComponent<RightDart>();
		Texture* texture = rightDart[i]->GetComponent<Texture>();
		texture->SetTexture(SDLFramework::Instance()->textures[20]);
		texture->SetFrameRate(0.13f);
		texture->SetHorizonCount(1);
		texture->SetVerticalCount(1);
		texture->SetBlendMode(SDL_BLENDMODE_BLEND);
		texture->SetAlpha(0xff);
		texture->SetAnimationActive(true);
		rightDart[i]->transform->SetWidth(50);
		rightDart[i]->transform->SetHeight(20);
	}

	PlayerHP = new SDLGameObject("PlayerHP");
	PlayerHP->AddComponent<Texture>();

	Texture* tex = PlayerHP->GetComponent<Texture>();
	tex->SetTexture(SDLFramework::Instance()->textures[39]);
	PlayerHP->transform->SetWidth(225);
	PlayerHP->transform->SetHeight(20);
	PlayerHP->transform->SetPosition(208,660);
	tex->SetBlendMode(SDL_BLENDMODE_ADD);

	GameManager::Instance()->RegisterObject(PlayerHP->name, PlayerHP);


}

Player::~Player()
{
}

void Player::OnCollisionEnter(Collider * other)
{
	State* state = gameObject->GetComponent<State>();
	if (state != NULL)
	{
		if (other->gameObject->GetComponent<RectangleCollider>()->colliderType == ZakumArmType)
		{
			state->SetHp(state->GetHp() - 1);
			cout << "충돌한 player의 hp = " << state->GetHp() << endl;
		}
		if (other->gameObject->GetComponent<RectangleCollider>()->colliderType == ZakumSkillType && other->gameObject->active)
		{
			state->SetHp(state->GetHp() - 1);
			cout << "스킬을맞은 player의 hp = " << state->GetHp() << endl;		
		}
		if (other->gameObject->GetComponent<RectangleCollider>()->colliderType == CreepType && other->gameObject->active)
		{
			state->SetHp(state->GetHp() - 1);
			cout << "스킬을맞은 player의 hp = " << state->GetHp() << endl;
		}		
	}
}

void Player::OnCollisionExit(Collider * other)
{
	Texture* tex = gameObject->GetComponent<Texture>();
	if (tex != NULL)
	{
		//tex->SetAlpha(0xFF);
	}
}

void Player::Update(float deltaTime)
{
	Texture* tex = PlayerHP->GetComponent<Texture>();
	if (tex != NULL)
	{
		PlayerHP->transform->SetWidth(gameObject->GetComponent<State>()->GetHp());
	}

	elapsedTime += deltaTime;
	if (attackState == 1) {
		if (elapsedTime > frameRate)
		{
			if (directionState == 1)
			{
				leftDart[leftDartCnt]->transform->SetPosition(gameObject->transform->projRect.x + 26, gameObject->transform->projRect.y + 35);
				leftDart[leftDartCnt]->GetComponent<LeftDart>()->accumulate = 0;
				leftDart[leftDartCnt]->GetComponent<LeftDart>()->Activate();

				leftDartCnt++;
				if (leftDartCnt != 0 && leftDartCnt % 6 == 0) {
					attackState = 0;
				}
			}

			if (directionState == 2)
			{
				rightDart[rightDartCnt]->transform->SetPosition(gameObject->transform->projRect.x + 26, gameObject->transform->projRect.y + 35);
				rightDart[rightDartCnt]->GetComponent<RightDart>()->accumulate = 0;
				rightDart[rightDartCnt]->GetComponent<RightDart>()->Activate();

				rightDartCnt++;
				if (rightDartCnt != 0 && rightDartCnt % 6 == 0) {
					attackState = 0;
				}
			}
			elapsedTime = 0;
		}
	}
	if (leftDartCnt == 18)
	{
		leftDartCnt = 0;
	}

	if (rightDartCnt == 18)
	{
		rightDartCnt = 0;
	}

	for (int i = 0; i < 18; i++)
	{
		leftDart[i]->Update(deltaTime);
	}

	for (int i = 0; i < 18; i++)
	{
		rightDart[i]->Update(deltaTime);
	}

}
void Player::Render()
{
	for (int i = 0; i < 18; i++)
	{
		if (leftDart[i]->active)
			leftDart[i]->Render();
	}

	for (int i = 0; i < 18; i++)
	{
		if (rightDart[i]->active)
			rightDart[i]->Render();
	}
}


