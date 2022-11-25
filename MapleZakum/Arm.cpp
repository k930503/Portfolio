#include "Arm.h"
#include "State.h"
#include "Texture.h"
#include "RectangleCollider.h"
#include "SDLFramework.h"
#include "Transform.h"
#include <iostream>

using namespace std;

Arm::Arm()
{
	rotateValue = 0.05;
	elapsedTime = 0.0f;
	frameRate	= 0.002f;
}
Arm::~Arm()
{
}

void Arm::Activate()
{
	gameObject->active = true;
}
void Arm::DeActivate()
{
	gameObject->active = false;
}

void Arm::OnCollisionEnter(Collider * other)
{
	State* state = gameObject->GetComponent<State>();
	if (state != NULL)
	{
		if (other->gameObject->GetComponent<RectangleCollider>()->colliderType == DartType && other->gameObject->active)
		{
			other->gameObject->active = false;
			state->SetHp(state->GetHp() - 10);
			cout << "��Ʈ������ Arm�� hp = " << state->GetHp() << endl;
		}
	}
}

void Arm::OnCollisionExit(Collider * other)
{
	Texture* tex = gameObject->GetComponent<Texture>();
	if (tex != NULL)
	{
		//tex->SetAlpha(0xFF);
	}
}

void Arm::Update(float deltaTime)
{
	if(gameObject->GetComponent<State>()->GetHp() <= 0){
		DeActivate();
		SDLFramework::Instance()->RemoveCollideGameObject(gameObject);
	}

	elapsedTime += deltaTime;
	if (elapsedTime > frameRate)
	{	
		gameObject->transform->SetRotate(gameObject->transform->rotate + rotateValue);
		gameObject->transform->SetAngle(sin(gameObject->transform->GetRotate()) * gameObject->transform->GetRange());	// ������ ���Ʒ��� �����̱�( �ﰢ�Լ� ���� �̿� )
		elapsedTime = 0.0f;
	}
}


