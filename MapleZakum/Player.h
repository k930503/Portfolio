#pragma once
#include "Component.h"
class Player :
	public Component
{
public:
	
	SDLGameObject* PlayerHP;
	SDLGameObject* leftDart[18];
	SDLGameObject* rightDart[18];

	float elapsedTime;	
	float frameRate;
	float duration;

	int leftDartCnt;
	int rightDartCnt;
	int attackState;
	int directionState;

	Player();
	~Player();

	void OnCollisionEnter(Collider * other);
	void OnCollisionExit(Collider * other);
	void Update(float deltaTime);
	void Render();
	
};

