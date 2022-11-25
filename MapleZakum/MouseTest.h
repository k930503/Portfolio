#pragma once
#include <iostream>
#include "Component.h"

class MouseTest :
	public Component
{
public:
	MouseTest();
	~MouseTest();

	Transform* linkedTransform = NULL;

	void HandleEvent(SDL_Event* e);
};

