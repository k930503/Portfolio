#pragma once
#include "Collider.h"
class RectangleCollider :
	public Collider
{

public:
	RectangleCollider();
	~RectangleCollider();

	SDL_Rect collisionRect;

	void Init();
	void Update(float deltaTime);
	bool isCollision(Collider* other);
};

