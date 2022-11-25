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

	void SummonCreep(int CreepNum); // ���� ��ȯ

	void Update(float deltaTime);
	void Damage();
	void DestroyCreep(); // ���� ���

	void OnCollisionEnter(Collider * other);
	void OnCollisionExit(Collider * other);
	void Render();
};

