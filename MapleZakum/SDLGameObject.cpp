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
	// 모든 컴포넌트 파기
	for (auto component : components)
	{
		if (component != NULL)
			delete component;
	}
	transform = NULL;
}

void SDLGameObject::Update(float deltaTime)
{
	// 모든 컴포넌트 Update
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
		// 각 Component 타입에 재정의된 HandleEvent가 호출된다.
		component->HandleEvent(e);
	}
}
