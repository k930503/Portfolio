#include "Thunder.h"

Thunder::Thunder()
{
	elapsedTime = 0.0f;
}
Thunder::~Thunder()
{
}

void Thunder::Activate()
{
	gameObject->active = true;
}
void Thunder::DeActivate()
{
	gameObject->active = false;
}
void Thunder::Update(float deltaTime)
{
	elapsedTime += deltaTime;

	if (elapsedTime > durationThunder)
	{
		DeActivate();
		elapsedTime = 0;
	}
}
