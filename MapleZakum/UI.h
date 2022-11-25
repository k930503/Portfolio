#pragma once
#include "Component.h"
class UI :
	public Component
{
public:
	SDLGameObject * All_UI;
	UI();
	~UI();
	void Update(float deltaTime);
	void Render();
};

