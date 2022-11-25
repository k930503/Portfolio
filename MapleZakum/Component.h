#pragma once
#include "SDLGameObject.h"

class SDLGameObject;
class Collider;

class Component
{
public:
	SDLGameObject* gameObject;

	Component() {};
	virtual ~Component() {};
	
	virtual void Init() {};
	virtual void HandleEvent(SDL_Event* e) {};
	virtual void Update(float deltaTime) {};
	virtual void Render() {};

	// Collision Functions
	virtual void OnCollisionEnter(Collider* other) {};
	virtual void OnCollisionStay(Collider* other) {};
	virtual void OnCollisionExit(Collider* other) {};
};

