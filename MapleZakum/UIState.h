#pragma once
#include "Component.h"
class UIState :
	public Component
{
public:
	int Hpbar = 0; //Hpbar 표시
	int Mpbar = 0;
	int ExpBar = 0;
	int current_PlayerHp = 0; // 현재 플레이어 Hp;
	int current_ZakumArm = 0; // 현재 자쿰팔 Hp;
	int current_ZakumBody = 0; // 현재 자쿰팔 Hp;
	int Units_Hp = 0; // 일의자리
	int Ten_Hp = 0;   // 십의자리
	int Hundreds_Hp = 0; // 백의자리
	int Ten_thousands_Hp = 0; // 천의자리

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

