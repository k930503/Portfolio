#pragma once
#include "Component.h"

enum FirePillarState
{
	Alarm,
	Fire,
	Destroy,
};

class FirePillar :
	public Component
{
	FirePillarState state;

	float elapsedTime;
	void SetState(FirePillarState _state);

	const float durationAlarm = 1.5f;
	const float durationFire = 0.65f;
	const float durationDestroy = 0.8f;

public:
	SDLGameObject* areaPreview;
	SDLGameObject* dropFire;
	SDLGameObject* destroyFire;
	FirePillar();
	FirePillar(const char* _name, SDLGameObject* _object);
	~FirePillar();

	void SetPosition(int x, int y);

	void Activate();
	void DeActivate();

	void Update(float deltaTime);
	void Render();
};

