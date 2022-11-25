#pragma once
#include "Component.h"
class Arm :
	public Component
{
	double				rotateValue;
	float				frameRate;
	float				elapsedTime;

public:
	Arm();
	~Arm();

	void Activate();
	void DeActivate();

	void OnCollisionEnter(Collider * other);
	void OnCollisionExit(Collider * other);

	void Update(float deltaTime);
};

