#pragma once
#include "Component.h"

class State : public Component
{
	int hp;
	int exp;

public:

	int GetHp();
	void SetHp(int _hp);
	int GetExp();
	void SetExp(int _exp);
	State();
	~State();
	void Update(float deltaTime);
};

