#pragma once
#include "Component.h"
class LeftDart :
	public Component
{
public:
	LeftDart();
	~LeftDart();
	float elapsedTime;
	float frameRate;
	int range;		// ��Ÿ�
	int accumulate;	// moving�� ������ (��Ÿ��� ������� ����)
	int moving;		// ������ ������ ��ġ

	void Activate();
	void DeActivate();

	void Update(float deltaTime);
};

