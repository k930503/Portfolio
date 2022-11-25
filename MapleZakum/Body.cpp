#include "Body.h"
#include "Texture.h"
#include "State.h"
#include "RectangleCollider.h"
#include "Transform.h"
#include "SDLFramework.h"
#include <iostream>
#include "GameManager.h"

using namespace std;

Body::Body()
{
	bodyHp = new SDLGameObject("ZakumHp");
	bodyHp->AddComponent<Texture>();

	Texture* tex = bodyHp->GetComponent<Texture>();
	tex->SetTexture(SDLFramework::Instance()->textures[39]);
	bodyHp->transform->SetWidth(0);
	bodyHp->transform->SetHeight(30);
	bodyHp->transform->SetPosition(0,0);

	GameManager::Instance()->RegisterObject(bodyHp->name, bodyHp);
}

Body::~Body()
{
}

void Body::Activate()
{
	gameObject->active = true;
}
void Body::DeActivate()
{
	gameObject->active = false;
}

void Body::OnCollisionEnter(Collider * other)
{
	State* state = gameObject->GetComponent<State>();
	if (state != NULL)
	{
		if (other->gameObject->GetComponent<RectangleCollider>()->colliderType == DartType && other->gameObject->active)
		{
			other->gameObject->active = false;
			state->SetHp(state->GetHp() - 4);
			cout << "다트를맞은 body의 hp = " << state->GetHp() << endl;
		}
	}
}

void Body::OnCollisionExit(Collider * other)
{
	Texture* tex = gameObject->GetComponent<Texture>();
	if (tex != NULL)
	{
		//tex->SetAlpha(0xFF);
	}
}

void Body::Update(float deltaTime)
{
	Texture* tex = bodyHp->GetComponent<Texture>();
	if (tex != NULL)
	{
		bodyHp->transform->SetWidth(gameObject->GetComponent<State>()->GetHp());

	}

	if (gameObject->GetComponent<Texture>()->GetFrameCount() == 15) 
	{
		DeActivate();
	}
}