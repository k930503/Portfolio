#include "LeftDart.h"
#include "Transform.h"


LeftDart::LeftDart()
{
	elapsedTime = 0.0f;
	frameRate	= 0.0f;
	range		= 500;
	accumulate	= 0;
	moving		= 10;
}

LeftDart::~LeftDart()
{
}

void LeftDart::Activate()
{
	gameObject->active = true;
}
void LeftDart::DeActivate()
{
	gameObject->active = false;
}

// 수리검 움직임
void LeftDart::Update(float deltaTime)
{
	gameObject->transform->projRect.x = (gameObject->transform->projRect.x) - moving;
	accumulate += moving;
	gameObject->transform->SetFlipMode(SDL_FLIP_HORIZONTAL);

	if (accumulate > range)
	{
		DeActivate();
		accumulate = 0;
	}
}