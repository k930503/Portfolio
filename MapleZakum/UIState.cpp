#include "UIState.h"
#include "Texture.h"
#include "SDLFramework.h"
#include "GameManager.h"
#include "Transform.h"

UIState::UIState()
{
}
UIState::~UIState()
{
}
void UIState::Update()
{
}

void UIState::PlayerCurrent_Hp(int _Hpbar)
{
}

void UIState::ZakumBodyCurrent_Hp(int _Hpbar)
{
}

void UIState::ZakumArmCurrent_Hp(int _Hpbar)
{
	Hpbar = _Hpbar;
	Units_Hp = Hpbar % 10;
	Ten_Hp = (Hpbar % 100) / 10;
	Hundreds_Hp = (Hpbar % 1000) / 100;
	Ten_thousands_Hp = (Hpbar % 10000) / 1000;
	cout << Hpbar << Units_Hp << Ten_Hp << Hundreds_Hp << Ten_thousands_Hp << endl;
}
void UIState::ZakumArmSetHp(int _ZakumArmHp) {
	current_ZakumArm = _ZakumArmHp;
	cout << current_ZakumArm << endl;
}

void UIState::ZakumBodySetHp(int _ZakumBodyHp)
{
	current_ZakumBody = _ZakumBodyHp;
}
void UIState::PlayerSetHp(int _PlayerHp)
{
	current_PlayerHp = _PlayerHp;
}
