#include "Creep.h"
#include "Texture.h"
#include "Transform.h"
#include "SDLFramework.h"
#include "CircleCollider.h"
#include "RectangleCollider.h"
#include "KeyboardTest.h"
#include "GameManager.h"
#include <random>
#include <Windows.h>
#include "State.h"

Creep::Creep()
{
	hit = dead = false;

	hp = 18;
	movX = 400;
	elapsedTime = 0.0f;
}

Creep::~Creep()
{
}

int Creep::getRandomNumber()
{
	//< 1�ܰ�. �õ� ����
	random_device rn;
	mt19937_64 rnd(rn());

	//< 2�ܰ�. ���� ���� ( ���� )
	uniform_int_distribution<int> range(-400,400);

	//< 3�ܰ�. �� ����
	return range(rnd);

}

// ���� ��ȭ�ƾ�!!
void Creep::SummonCreep(int CreepNum) 
{
	SDLGameObject*	obj;
	Texture*		tex;

	obj = new SDLGameObject("Creep" + CreepNum);
	tex = obj->AddComponent<Texture>();
	obj->AddComponent<Creep>();
	tex->SetTexture(SDLFramework::Instance()->textures[71]);
	tex->SetFrameRate(0.1f);
	tex->SetHorizonCount(6);
	tex->SetVerticalCount(1);
	tex->SetAnimationActive(true);
	obj->transform->SetPosition(400, 350);
	obj->transform->SetWidth(144);
	obj->transform->SetHeight(188);
	obj->AddComponent<RectangleCollider>();
	GameManager::Instance()->RegisterObject(obj->name, obj);
	SDLFramework::Instance()->AddCollideGameObject(obj);
}

void Creep::Update(float deltaTime)
{
	Texture* tex = gameObject->GetComponent<Texture>();

	if (!dead && !hit) // ���Ͱ� ����ִ� ��� ������ ��ġ(movX)�� �����δ�
	{
		if(movX != gameObject->transform->GetxPos())
		{
			if (movX < gameObject->transform->GetxPos())
			{
				gameObject->transform->Move(-2, 0);
				gameObject->transform->SetFlipMode(SDL_FLIP_NONE);
			}

			else if (movX > gameObject->transform->GetxPos())
			{
				gameObject->transform->Move(2, 0);
				gameObject->transform->SetFlipMode(SDL_FLIP_HORIZONTAL);
			}
		}
		else // ������ ��ġ�� �̵� �Ϸ��� ��� movX ���� �缳�� 
		{
			movX += getRandomNumber();
			movX -= movX % 2;
			if (movX < 100) // ���Ͱ� �������� ����� �ʰ�
				movX = 100;
			else if (movX > WINDOWS_WIDTH) // �������� ����� �ʰ� 
				movX = WINDOWS_WIDTH - 236;
		}
	} 
	else if (hit) // �¾��� ���
	{
		elapsedTime += deltaTime;
		Damage();
	}

	if (dead && tex->GetFrameCount() == 7) // �׾��� ���
	{
		tex->SetAnimationActive(false);
		tex->SetAlpha(0x00);
		gameObject->active = false;
		elapsedTime += deltaTime;
		float timer = 30.0f;

		if (elapsedTime >= timer) // �ð� ������ ���ȯ
		{
			tex->SetTexture(SDLFramework::Instance()->textures[71]);
			tex->SetFrameRate(0.1f);
			tex->SetHorizonCount(6);
			tex->SetVerticalCount(1);
			tex->SetAnimationActive(true);
			gameObject->transform->SetPosition(400, 350);
			gameObject->active = true;
			dead = false;
			hp = 18;
		}
	}
}

//������ �Լ��� ��õ��� ���͸� �󸮴� ����
void Creep::Damage()
{
	Texture* tex = gameObject->GetComponent<Texture>();

	if (elapsedTime <= 0.5f)
	{
		tex->SetTexture(SDLFramework::Instance()->textures[72]);
		tex->SetAnimationActive(false);
		tex->SetVerticalCount(1);
		tex->SetHorizonCount(1);				
	}
	else 
	{
		tex->SetTexture(SDLFramework::Instance()->textures[71]);
		tex->SetFrameRate(0.1f);
		tex->SetHorizonCount(6);
		tex->SetVerticalCount(1);
		tex->SetAnimationActive(true);
		elapsedTime = 0.0f;
		hit = false;
	}
}

void Creep::DestroyCreep()
{
	Texture* tex = gameObject->GetComponent<Texture>();
	tex->SetFrameCount(0);
	tex->SetTexture(SDLFramework::Instance()->textures[73]);
	tex->SetFrameRate(0.1f);
	tex->SetHorizonCount(8);
	tex->SetVerticalCount(1);
	tex->SetAnimationActive(true);
}

void Creep::OnCollisionEnter(Collider * other)
{
	if (!dead && other->gameObject->GetComponent<RectangleCollider>()->colliderType == PlayerType)
	{
		other->gameObject->GetComponent<State>()->SetHp(other->gameObject->GetComponent<State>()->GetHp() - 1);
	}

	if (!dead && other->gameObject->GetComponent<RectangleCollider>()->colliderType == DartType && other->gameObject->active)
	{
		other->gameObject->active = false;

		hp --;

		cout << "��Ʈ������ ����� hp = " << hp << endl;
		if (hp <= 0)
		{
			hit = false;
			dead = true;
			DestroyCreep();
		}
		else
			hit = true;
	}
}

void Creep::OnCollisionExit(Collider * other)
{
}

void Creep::Render()
{
	if (!dead)
	{
	}
}
