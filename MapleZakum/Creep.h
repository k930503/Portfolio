#pragma once
#include "Component.h"

enum CreepDir{
	leftdir,
	rightdir,
};

class Creep :
	public Component
{
protected:
	bool hit;
	bool dead;
	int hp;
	int movX;

	float elapsedTime;
	unsigned int frameCount;
	CreepDir dir;
public:
	Creep();
	~Creep();

	int getRandomNumber();

	void SummonCreep(int CreepNum); // 몬스터 소환

	void Update(float deltaTime);
	void Damage();
	void DestroyCreep(); // 몬스터 사망

	void OnCollisionEnter(Collider * other);
	void OnCollisionExit(Collider * other);
	void Render();
};

