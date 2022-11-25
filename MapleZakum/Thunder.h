#pragma once
#include "Component.h"
class Thunder :
	public Component
{
public:

	float elapsedTime;

	const float durationThunder = 0.8f;

	Thunder();
	~Thunder();

	void Activate();
	void DeActivate();

	void Update(float deltaTime);
	
};

