#include "State.h"



State::State()
{
	hp = 0;
	exp = 100;
}
State::~State()
{
}

int State::GetHp()
{
	return hp;
}
void State::SetHp(int _hp) 
{
	hp = _hp;
}
int State::GetExp()
{
	return exp;
}
void State::SetExp(int _exp)
{
	exp = _exp;
}

void State::Update(float deltaTime) 
{
}
