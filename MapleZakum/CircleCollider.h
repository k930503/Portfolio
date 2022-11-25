#pragma once
#include "Collider.h"
class CircleCollider :
	public Collider
{
	void UpdateCenter();

public:
	int centerX;
	int centerY;
	int radius;

	CircleCollider();
	~CircleCollider();

	void Init();
	void Update(float deltaTime);
	bool isCollision(Collider* other);
};

