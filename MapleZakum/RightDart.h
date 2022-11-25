#pragma once
#include "Component.h"
class RightDart :
	public Component
{
public:
	RightDart();
	~RightDart();
	float elapsedTime;
	float frameRate;
	int range;		// 사거리
	int accumulate;	// moving을 누산함 (사거리를 재기위한 변수
	int moving;		// 수리검 움직임

	void Activate();
	void DeActivate();

	void Update(float deltaTime);
};

