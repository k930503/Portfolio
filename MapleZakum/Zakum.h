#pragma once
#include "Component.h"
class Zakum :
	public Component
{ 
	SDLGameObject* body;
	SDLGameObject* arm[8];
	SDLGameObject* firePillar[7];
	SDLGameObject* thunder[7];

	bool armDieCheck = true;
	bool body2ChangeCheck = true;
	bool body3ChangeCheck = true;
	bool body3DieCheck = true;

public:

	float				frameRate;
	float				elapsedTime;

	Zakum();
	~Zakum();
	void Update(float deltaTime);
	void Render();
};

