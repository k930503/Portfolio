#pragma once
#include "Component.h"
class UIState :
	public Component
{
public:
	int Hpbar = 0; //Hpbar ǥ��
	int Mpbar = 0;
	int ExpBar = 0;
	int current_PlayerHp = 0; // ���� �÷��̾� Hp;
	int current_ZakumArm = 0; // ���� ������ Hp;
	int current_ZakumBody = 0; // ���� ������ Hp;
	int Units_Hp = 0; // �����ڸ�
	int Ten_Hp = 0;   // �����ڸ�
	int Hundreds_Hp = 0; // �����ڸ�
	int Ten_thousands_Hp = 0; // õ���ڸ�

	SDLGameObject * All_UIState;
	UIState();
	~UIState();

	void Update();

	void PlayerCurrent_Hp(int _Hpbar);
	void ZakumBodyCurrent_Hp(int _Hpbar);
	void ZakumArmCurrent_Hp(int _Hpbar);
	void ZakumArmSetHp(int _ZakumArmHp);
	void ZakumBodySetHp(int _ZakumBodyHp);
	void PlayerSetHp(int _PlayerHp);
};

