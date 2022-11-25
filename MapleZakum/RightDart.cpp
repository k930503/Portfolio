#include "RightDart.h"
#include "Transform.h"


RightDart::RightDart()
{
	elapsedTime = 0.0f;
	frameRate	= 0.0f;
	range		= 500;
	accumulate	= 0;
	moving		= 10;
}

RightDart::~RightDart()
{
}

void RightDart::Activate()
{
	gameObject->active = true;
}
void RightDart::DeActivate()
{
	gameObject->active = false;
}

// 수리검 움직임
void RightDart::Update(float deltaTime)
{
	gameObject->transform->projRect.x = (gameObject->transform->projRect.x) + moving;
	accumulate += moving;

	if (accumulate > range)
	{
		DeActivate();
		accumulate = 0;
	}
}
