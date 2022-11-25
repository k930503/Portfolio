#include "UI.h"
#include "SDLFramework.h"
#include "GameManager.h"
#include "Utilities.h"
#include "Texture.h"
#include "Transform.h"
#include "Zakum.h"
#include "State.h"
#include "Body.h"
#include "UIState.h"

UI::UI()
{

	// 백그라운드
	All_UI = new SDLGameObject("StatGrds");
	Texture* texture = All_UI->AddComponent<Texture>();
	texture->SetTexture(SDLFramework::Instance()->textures[21]);
	All_UI->transform->SetWidth(1280);
	All_UI->transform->SetHeight(100);
	All_UI->transform->SetPosition(0, 600);
	GameManager::Instance()->RegisterObject(All_UI->name, All_UI);

	// 레벨바
	All_UI = new SDLGameObject("Levelbar");
	texture = All_UI->AddComponent<Texture>();
	texture->SetTexture(SDLFramework::Instance()->textures[22]);
	All_UI->transform->SetWidth(180);
	All_UI->transform->SetHeight(40);
	All_UI->transform->SetPosition(0, 660);
	GameManager::Instance()->RegisterObject(All_UI->name, All_UI);

	// 레벨 십의자리
	All_UI = new SDLGameObject("TenLevel");
	texture = All_UI->AddComponent<Texture>();
	texture->SetTexture(SDLFramework::Instance()->textures[25]);
	All_UI->transform->SetWidth(20);
	All_UI->transform->SetHeight(20);
	All_UI->transform->SetPosition(35, 670);
	GameManager::Instance()->RegisterObject(All_UI->name, All_UI);

	// 레벨 일의자리

	All_UI = new SDLGameObject("UnitsLevel");
	texture = All_UI->AddComponent<Texture>();
	texture->SetTexture(SDLFramework::Instance()->textures[26]);
	All_UI->transform->SetWidth(20);
	All_UI->transform->SetHeight(20);
	All_UI->transform->SetPosition(60, 670);
	GameManager::Instance()->RegisterObject(All_UI->name, All_UI);


	// 채팅바
	All_UI = new SDLGameObject("ChatBase");
	texture = All_UI->AddComponent<Texture>();
	texture->SetTexture(SDLFramework::Instance()->textures[33]);
	All_UI->transform->SetWidth(120);
	All_UI->transform->SetHeight(30);
	All_UI->transform->SetPosition(0, 630);
	GameManager::Instance()->RegisterObject(All_UI->name, All_UI);

	All_UI = new SDLGameObject("ChatAll");
	texture = All_UI->AddComponent<Texture>();
	texture->SetTexture(SDLFramework::Instance()->textures[34]);
	All_UI->transform->SetWidth(120);
	All_UI->transform->SetHeight(30);
	All_UI->transform->SetPosition(0, 630);
	GameManager::Instance()->RegisterObject(All_UI->name, All_UI);

	All_UI = new SDLGameObject("ChatEnter");
	texture = All_UI->AddComponent<Texture>();
	texture->SetTexture(SDLFramework::Instance()->textures[35]);
	All_UI->transform->SetWidth(350);
	All_UI->transform->SetHeight(30);
	All_UI->transform->SetPosition(120, 630);
	GameManager::Instance()->RegisterObject(All_UI->name, All_UI);

	All_UI = new SDLGameObject("BtChat");
	texture = All_UI->AddComponent<Texture>();
	texture->SetTexture(SDLFramework::Instance()->textures[36]);
	All_UI->transform->SetWidth(30);
	All_UI->transform->SetHeight(30);
	All_UI->transform->SetPosition(470, 630);
	GameManager::Instance()->RegisterObject(All_UI->name, All_UI);

	All_UI = new SDLGameObject("BtClaim");
	texture = All_UI->AddComponent<Texture>();
	texture->SetTexture(SDLFramework::Instance()->textures[37]);
	All_UI->transform->SetWidth(30);
	All_UI->transform->SetHeight(30);
	All_UI->transform->SetPosition(500, 630);
	GameManager::Instance()->RegisterObject(All_UI->name, All_UI);

	// 상태바
	All_UI = new SDLGameObject("BackGrdStatus");
	texture = All_UI->AddComponent<Texture>();
	texture->SetTexture(SDLFramework::Instance()->textures[38]);
	All_UI->transform->SetWidth(350);
	All_UI->transform->SetHeight(40);
	All_UI->transform->SetPosition(180, 660);
	GameManager::Instance()->RegisterObject(All_UI->name, All_UI);

	All_UI = new SDLGameObject("HP_Left");
	texture = All_UI->AddComponent<Texture>();
	texture->SetTexture(SDLFramework::Instance()->textures[44]);
	All_UI->transform->SetWidth(10);
	All_UI->transform->SetHeight(15);
	All_UI->transform->SetPosition(240, 660);
	GameManager::Instance()->RegisterObject(All_UI->name, All_UI);

	//hp 슬러쉬
	All_UI = new SDLGameObject("HP_Slash");
	texture = All_UI->AddComponent<Texture>();
	texture->SetTexture(SDLFramework::Instance()->textures[56]);
	All_UI->transform->SetWidth(10);
	All_UI->transform->SetHeight(15);
	All_UI->transform->SetPosition(290, 660);
	GameManager::Instance()->RegisterObject(All_UI->name, All_UI);

	//hp 천의자리
	All_UI = new SDLGameObject("thousands_HP");
	texture = All_UI->AddComponent<Texture>();
	texture->SetTexture(SDLFramework::Instance()->textures[46]);
	All_UI->transform->SetWidth(10);
	All_UI->transform->SetHeight(10);
	All_UI->transform->SetPosition(300, 660);
	GameManager::Instance()->RegisterObject(All_UI->name, All_UI);
	//hp 백의자리
	All_UI = new SDLGameObject("hundreds _HP");
	texture = All_UI->AddComponent<Texture>();
	texture->SetTexture(SDLFramework::Instance()->textures[47]);
	All_UI->transform->SetWidth(10);
	All_UI->transform->SetHeight(10);
	All_UI->transform->SetPosition(310, 660);
	GameManager::Instance()->RegisterObject(All_UI->name, All_UI);
	//hp 십의자리
	All_UI = new SDLGameObject("tens_HP");
	texture = All_UI->AddComponent<Texture>();
	texture->SetTexture(SDLFramework::Instance()->textures[48]);
	All_UI->transform->SetWidth(10);
	All_UI->transform->SetHeight(10);
	All_UI->transform->SetPosition(320, 660);
	GameManager::Instance()->RegisterObject(All_UI->name, All_UI);
	//hp 일의자리
	All_UI = new SDLGameObject("units_HP");
	texture = All_UI->AddComponent<Texture>();
	texture->SetTexture(SDLFramework::Instance()->textures[49]);
	All_UI->transform->SetWidth(10);
	All_UI->transform->SetHeight(10);
	All_UI->transform->SetPosition(330, 660);
	GameManager::Instance()->RegisterObject(All_UI->name, All_UI);

	//hp ]
	All_UI = new SDLGameObject("HP_Right");
	texture = All_UI->AddComponent<Texture>();
	texture->SetTexture(SDLFramework::Instance()->textures[45]);
	All_UI->transform->SetWidth(10);
	All_UI->transform->SetHeight(15);
	All_UI->transform->SetPosition(340, 660);
	GameManager::Instance()->RegisterObject(All_UI->name, All_UI);

	//MP  
	All_UI = new SDLGameObject("MpBar");
	texture = All_UI->AddComponent<Texture>();
	texture->SetTexture(SDLFramework::Instance()->textures[40]);
	All_UI->transform->SetWidth(145);
	All_UI->transform->SetHeight(21);
	All_UI->transform->SetPosition(385, 660);
	texture->SetBlendMode(SDL_BLENDMODE_ADD);
	GameManager::Instance()->RegisterObject(All_UI->name, All_UI);

	//EXP 
	All_UI = new SDLGameObject("ExpBar");
	texture = All_UI->AddComponent<Texture>();
	texture->SetTexture(SDLFramework::Instance()->textures[41]);
	All_UI->transform->SetWidth(220);
	All_UI->transform->SetHeight(20);
	All_UI->transform->SetPosition(208, 680);
	GameManager::Instance()->RegisterObject(All_UI->name, All_UI);


	// 그외 상태창 57~ 71
	All_UI = new SDLGameObject("BtNotic");
	texture = All_UI->AddComponent<Texture>();
	texture->SetTexture(SDLFramework::Instance()->textures[57]);
	All_UI->transform->SetWidth(30);
	All_UI->transform->SetHeight(30);
	All_UI->transform->SetPosition(530, 630);
	GameManager::Instance()->RegisterObject(All_UI->name, All_UI);

	All_UI = new SDLGameObject("BtCharacter");
	texture = All_UI->AddComponent<Texture>();
	texture->SetTexture(SDLFramework::Instance()->textures[58]);
	All_UI->transform->SetWidth(30);
	All_UI->transform->SetHeight(30);
	All_UI->transform->SetPosition(560, 630);
	GameManager::Instance()->RegisterObject(All_UI->name, All_UI);

	All_UI = new SDLGameObject("BtStat");
	texture = All_UI->AddComponent<Texture>();
	texture->SetTexture(SDLFramework::Instance()->textures[59]);
	All_UI->transform->SetWidth(30);
	All_UI->transform->SetHeight(30);
	All_UI->transform->SetPosition(590, 630);
	GameManager::Instance()->RegisterObject(All_UI->name, All_UI);

	All_UI = new SDLGameObject("BtQuest");
	texture = All_UI->AddComponent<Texture>();
	texture->SetTexture(SDLFramework::Instance()->textures[60]);
	All_UI->transform->SetWidth(30);
	All_UI->transform->SetHeight(30);
	All_UI->transform->SetPosition(620, 630);
	GameManager::Instance()->RegisterObject(All_UI->name, All_UI);

	All_UI = new SDLGameObject("BtInven");
	texture = All_UI->AddComponent<Texture>();
	texture->SetTexture(SDLFramework::Instance()->textures[61]);
	All_UI->transform->SetWidth(30);
	All_UI->transform->SetHeight(30);
	All_UI->transform->SetPosition(650, 630);
	GameManager::Instance()->RegisterObject(All_UI->name, All_UI);

	All_UI = new SDLGameObject("BtEquip");
	texture = All_UI->AddComponent<Texture>();
	texture->SetTexture(SDLFramework::Instance()->textures[62]);
	All_UI->transform->SetWidth(30);
	All_UI->transform->SetHeight(30);
	All_UI->transform->SetPosition(680, 630);
	GameManager::Instance()->RegisterObject(All_UI->name, All_UI);

	All_UI = new SDLGameObject("BtSkill");
	texture = All_UI->AddComponent<Texture>();
	texture->SetTexture(SDLFramework::Instance()->textures[63]);
	All_UI->transform->SetWidth(30);
	All_UI->transform->SetHeight(30);
	All_UI->transform->SetPosition(710, 630);
	GameManager::Instance()->RegisterObject(All_UI->name, All_UI);

	All_UI = new SDLGameObject("BtFarm");
	texture = All_UI->AddComponent<Texture>();
	texture->SetTexture(SDLFramework::Instance()->textures[64]);
	All_UI->transform->SetWidth(30);
	All_UI->transform->SetHeight(30);
	All_UI->transform->SetPosition(760, 630);
	GameManager::Instance()->RegisterObject(All_UI->name, All_UI);

	All_UI = new SDLGameObject("BtKeysetting");
	texture = All_UI->AddComponent<Texture>();
	texture->SetTexture(SDLFramework::Instance()->textures[65]);
	All_UI->transform->SetWidth(30);
	All_UI->transform->SetHeight(30);
	All_UI->transform->SetPosition(790, 630);
	GameManager::Instance()->RegisterObject(All_UI->name, All_UI);

	All_UI = new SDLGameObject("BtCashShop");
	texture = All_UI->AddComponent<Texture>();
	texture->SetTexture(SDLFramework::Instance()->textures[66]);
	All_UI->transform->SetWidth(55);
	All_UI->transform->SetHeight(40);
	All_UI->transform->SetPosition(535, 660);
	GameManager::Instance()->RegisterObject(All_UI->name, All_UI);

	All_UI = new SDLGameObject("BtStarPlant");
	texture = All_UI->AddComponent<Texture>();
	texture->SetTexture(SDLFramework::Instance()->textures[67]);
	All_UI->transform->SetWidth(55);
	All_UI->transform->SetHeight(40);
	All_UI->transform->SetPosition(585, 660);
	GameManager::Instance()->RegisterObject(All_UI->name, All_UI);

	All_UI = new SDLGameObject("BtMenu");
	texture = All_UI->AddComponent<Texture>();
	texture->SetTexture(SDLFramework::Instance()->textures[68]);
	All_UI->transform->SetWidth(55);
	All_UI->transform->SetHeight(40);
	All_UI->transform->SetPosition(635, 660);
	GameManager::Instance()->RegisterObject(All_UI->name, All_UI);

	All_UI = new SDLGameObject("BtSystem");
	texture = All_UI->AddComponent<Texture>();
	texture->SetTexture(SDLFramework::Instance()->textures[69]);
	All_UI->transform->SetWidth(55);
	All_UI->transform->SetHeight(40);
	All_UI->transform->SetPosition(685, 660);
	GameManager::Instance()->RegisterObject(All_UI->name, All_UI);

	All_UI = new SDLGameObject("BtChannel");
	texture = All_UI->AddComponent<Texture>();
	texture->SetTexture(SDLFramework::Instance()->textures[70]);
	All_UI->transform->SetWidth(70);
	All_UI->transform->SetHeight(40);
	All_UI->transform->SetPosition(750, 660);
	GameManager::Instance()->RegisterObject(All_UI->name, All_UI);
}

UI::~UI()
{
}

void UI::Update(float deltaTime)
{
}

void UI::Render()
{
	All_UI->Render();
}
