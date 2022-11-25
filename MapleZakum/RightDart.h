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
	int range;		// ��Ÿ�
	int accumulate;	// moving�� ������ (��Ÿ��� ������� ����
	int moving;		// ������ ������

	void Activate();
	void DeActivate();

	void Update(float deltaTime);
};

