#include "Collider.h"
#include "SDLFramework.h"
#include "Transform.h"
#include "GameManager.h"

Collider::Collider()
{
}

Collider::~Collider()
{
}

void Collider::Update(float deltaTime)
{
	for (auto object : SDLFramework::Instance()->GetCollideObjectList())
	{
		if (object->active && gameObject->active) {
			Collider* other = object->GetComponent<Collider>();
			if (other == NULL || other == this)
				continue;


			if (isCollision(other))
			{
				gameObject->OnCollisionEnter(other);
			}
			else
			{
				gameObject->OnCollisionExit(other);
			}
		}
			
	}
}
