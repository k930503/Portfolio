#pragma once
#include "Component.h"
class Body :
	public Component
{
public:
	
	SDLGameObject * bodyHp;

	Body();
	~Body();

	void Activate();
	void DeActivate();

	void OnCollisionEnter(Collider * other);
	void OnCollisionExit(Collider * other);

	void Update(float deltaTime);
};

