#include "SDLGameObject.h"
#include "Utilities.h"
#include "Transform.h"
#include "Texture.h"
#include "Component.h"

SDLGameObject::SDLGameObject(const char* _name)
{
	transform = AddComponent<Transform>();
	name = _name;
	transform->name = _name;
}

SDLGameObject::SDLGameObject(const char* _name, bool _active) {

	transform = AddComponent<Transform>();
	name = _name;
	active = _active;
}
SDLGameObject::SDLGameObject(const char* _name, double _rotate, double _range)
{
	transform = AddComponent<Transform>();

	name = _name;
	transform->rotate = _rotate;
	transform->name = _name;
	transform->range = _range;
}

SDLGameObject::~SDLGameObject()
{
	// ��� ������Ʈ �ı�
	for (auto component : components)
	{
		if (component != NULL)
			delete component;
	}
	transform = NULL;
}

void SDLGameObject::Update(float deltaTime)
{
	// ��� ������Ʈ Update
	for (auto component : components)
	{
		component->Update(deltaTime);
	}
}

void SDLGameObject::Render()
{
	for (auto component : components)
	{
		component->Render();
	}
}

void SDLGameObject::OnCollisionEnter(Collider * other)
{
	for (auto component : components)
	{
		component->OnCollisionEnter(other);
	}
}

void SDLGameObject::OnCollisionStay(Collider * other)
{
	for (auto component : components)
	{
		component->OnCollisionStay(other);
	}
}

void SDLGameObject::OnCollisionExit(Collider * other)
{
	for (auto component : components)
	{
		component->OnCollisionExit(other);
	}
}

void SDLGameObject::HandleEvent(SDL_Event * e)
{
	for (auto component : components)
	{
		// �� Component Ÿ�Կ� �����ǵ� HandleEvent�� ȣ��ȴ�.
		component->HandleEvent(e);
	}
}
