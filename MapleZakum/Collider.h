#pragma once
#include "Component.h"

enum ColliderType
{
	ZakumBodytype,
	ZakumArmType,
	ZakumSkillType,
	ZakumCreepType,
	PlayerType,
	DartType,
	CreepType,
};
class Collider :
	public Component
{
public:
	ColliderType colliderType;

	Collider();
	virtual ~Collider();

	void Update(float deltaTime);
	virtual bool isCollision(Collider* other) = 0;
};

