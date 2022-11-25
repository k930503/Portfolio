#pragma once
#include "Component.h"

class Collider;

class KeyboardTest :
	public Component
{
public:
	float elapsedTime;
	float frameRate;
	
	int dir;
	
	KeyboardTest();
	~KeyboardTest();

	void Update(float deltaTime);
};

