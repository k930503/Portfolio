#include "SDLFramework.h"
#include "GameManager.h"
#include "Utilities.h"
#include "Texture.h"
#include "Transform.h"
#include "Text.h"
#include "MouseTest.h"
#include "KeyboardTest.h"
#include "RectangleCollider.h"
#include "CircleCollider.h"
#include "Zakum.h"
#include "Player.h"
#include "State.h"
#include "Creep.h"
#include "UI.h"
#include "UIState.h"

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

void GameManager::Init()
{
	// 게임에 필요한 오브젝트 또는 Scene 들을 초기 배치 및 등록

	// 폰트 로드
	SDLFramework::Instance()->RegisterFont("./Media/Font/DiabloLight.ttf", 48);

	SDL_Texture* tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/background.png");  // 배경 0
	SDLFramework::Instance()->textures.push_back(tex);

	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/arm1.png", 0xFF, 0xFF, 0xFF);
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/arm2.png", 0xFF, 0xFF, 0xFF);
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/arm3.png", 0xFF, 0xFF, 0xFF);
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/arm4.png", 0xFF, 0xFF, 0xFF);
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/arm5.png", 0xFF, 0xFF, 0xFF);
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/arm6.png", 0xFF, 0xFF, 0xFF);
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/arm7.png", 0xFF, 0xFF, 0xFF);
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/arm8.png", 0xFF, 0xFF, 0xFF); // 팔 8
	SDLFramework::Instance()->textures.push_back(tex);


	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/zakumBody1.png");  // 몸 9
	SDLFramework::Instance()->textures.push_back(tex);

	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/firepillarCue.png", 0xFF, 0xFF, 0xFF);  // 불기둥 10
	SDLFramework::Instance()->textures.push_back(tex);

	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/fireDrop.png", 0xFF, 0xFF, 0xFF);
	SDLFramework::Instance()->textures.push_back(tex);

	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/destroyFire.png", 255, 255, 255);
	SDLFramework::Instance()->textures.push_back(tex);

	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/thunder.png", 255, 255, 255);  // 번개 13
	SDLFramework::Instance()->textures.push_back(tex);

	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/secondPhase.png", 255, 0, 255); // 몸2 14
	SDLFramework::Instance()->textures.push_back(tex);

	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/zakumDie.png");  // 몸 무너지는거 15
	SDLFramework::Instance()->textures.push_back(tex);

	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/stopMotion.png");  // 정지모션 16
	SDLFramework::Instance()->textures.push_back(tex);

	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/moveMotion.png");  // 움직임모션 17
	SDLFramework::Instance()->textures.push_back(tex);

	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/jumpMotion.png");  // 점프모션 18
	SDLFramework::Instance()->textures.push_back(tex);

	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/attackMotion.png");  // 공격 모션 19
	SDLFramework::Instance()->textures.push_back(tex);

	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/Dart.png");  // 표창 20
	SDLFramework::Instance()->textures.push_back(tex);

	// UI 21~
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/statusgrd.png");  // 배경 0
	SDLFramework::Instance()->textures.push_back(tex);

	// 레벨바 22~32
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/LvKinesis.png"); // 레벨바
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/lvNumber0.png"); // 숫자0
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/lvNumber1.png"); // 숫자1
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/lvNumber2.png"); // 숫자2
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/lvNumber3.png"); // 숫자3
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/lvNumber4.png"); // 숫자4
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/lvNumber5.png"); // 숫자5
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/lvNumber6.png"); // 숫자6
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/lvNumber7.png"); // 숫자7
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/lvNumber8.png"); // 숫자8
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/lvNumber9.png"); // 숫자9
	SDLFramework::Instance()->textures.push_back(tex);

	// 채팅바 33~37
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/chatBase.png"); // 레벨바
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/chatAll.png"); // 레벨바
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/chatEnter.png"); // 레벨바
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/BtChat.png"); // 레벨바
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/BtClaim.png"); // 레벨바
	SDLFramework::Instance()->textures.push_back(tex);

	// 상태바 38
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/gaugeBackgrd.png"); // 레벨바
	SDLFramework::Instance()->textures.push_back(tex);
	//HP 															   
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/hp.png"); // HP
	SDLFramework::Instance()->textures.push_back(tex);
	//UI MP 															   
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/mp.png"); // MP
	SDLFramework::Instance()->textures.push_back(tex);
	//UI EXP															   
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/Exp.png"); // EXP
	SDLFramework::Instance()->textures.push_back(tex);

	//UI GaugeNumber 42~56											  
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/gauge%.png"); // %
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/gauge..png"); // .
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/gauge[.png"); // [
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/gauge].png"); // ]
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/gauge0.png"); // 0
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/gauge1.png"); // 1
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/gauge2.png"); // 2
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/gauge3.png"); // 3
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/gauge4.png"); // 4
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/gauge5.png"); // 5
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/gauge6.png"); // 6
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/gauge7.png"); // 7
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/gauge8.png"); // 8
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/gauge9.png"); // 9
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/gaugeSlash.png"); // /
	SDLFramework::Instance()->textures.push_back(tex);

	// 기타 status 창 57 ~ 71
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/BtNotic.png"); // /
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/BtCharacter.png"); // /
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/BtStat.png"); // /
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/BtQuest.png"); // /
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/BtInven.png"); // /
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/BtEquip.png"); // /
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/BtSkill.png"); // /
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/BtFarm.png"); // /
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/BtKeysetting.png"); // /

	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/BtCashShop.png"); // /
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/BtStarPlant.png"); // /
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/BtMenu.png"); // /
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/BtSystem.png"); // /
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/BtChannel.png"); // /
	SDLFramework::Instance()->textures.push_back(tex);

	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/creep.png");  // 몬스터 70
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/creep_hit.png");  // 몬스터 아파 71
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/creep_die.png");  // 몬스터 주거 72
	SDLFramework::Instance()->textures.push_back(tex);

	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/cap.png");  // 몬스터 주거 72
	SDLFramework::Instance()->textures.push_back(tex);

	SDLGameObject* obj = new SDLGameObject("Background");
	Texture* texture = obj->AddComponent<Texture>();
	texture->SetTexture(SDLFramework::Instance()->textures[0]);
	texture->SetHorizonCount(1);
	texture->SetVerticalCount(1);
	obj->transform->SetPosition(0, 0);
	obj->transform->SetWidth(1280);
	obj->transform->SetHeight(720);
	RegisterObject(obj->name, obj);

	// 자쿰생성
	obj = new SDLGameObject("Zakum");
	obj->AddComponent<Zakum>();
	RegisterObject(obj->name, obj);

	// UI생성
	obj = new SDLGameObject("Ui");
	obj->AddComponent<UI>();
	obj->AddComponent<UIState>();
	RegisterObject(obj->name, obj);


	// 플레이어 오브젝트 생성
	obj = new SDLGameObject("Character");
	obj->AddComponent<Player>();
	obj->AddComponent<Texture>();
	obj->AddComponent<State>();
	obj->AddComponent<RectangleCollider>();
	obj->AddComponent<KeyboardTest>();
	State* state = obj->GetComponent<State>();
	state->SetHp(144);
	texture = obj->AddComponent<Texture>();
	texture->SetTexture(SDLFramework::Instance()->textures[16]);
	obj->transform->SetWidth(52);
	obj->transform->SetHeight(71);
	texture->SetFrameRate(0.3f);
	texture->SetHorizonCount(3);
	texture->SetVerticalCount(1);
	texture->SetAnimationActive(true);
	RectangleCollider* collider = obj->GetComponent<RectangleCollider>();
	collider->colliderType = PlayerType;
	SDLFramework::Instance()->collideObj.insert(pair<string, SDLGameObject*>(obj->name, obj));
	SDLFramework::Instance()->AddCollideGameObject(obj);
	RegisterObject(obj->name, obj);

	// 크립 소환
	Creep *creep[5];
	int CreepNum = 0;
	for (auto i : creep)
	{
		i = new Creep();
		i->SummonCreep(CreepNum);
		CreepNum += 1;
	}
}

void GameManager::RegisterObject(string key, SDLGameObject* object)
{
	if (contentObjects.find(key) != contentObjects.end())
	{
		cout << key << " : 이미 등록된 키가 있습니다. Object 등록에 실패 하였습니다."
			<< endl;
		
		delete object;
		return;
	}

	contentObjects.insert(pair<string, SDLGameObject*>(key, object));
	SDLFramework::Instance()->AddGameObject(object);
}

SDLGameObject* GameManager::GetObject(string key)
{
	map<string, SDLGameObject*>::iterator iter = contentObjects.find(key);
	if (iter != contentObjects.end())
	{
		return iter->second;
	}

	return NULL;
}

void GameManager::DestroyObject(string key)
{
	map<string, SDLGameObject*>::iterator iter = contentObjects.find(key);
	if (iter != contentObjects.end())
	{
		SDLFramework::Instance()->RemoveGameObject(iter->second);
		contentObjects.erase(iter);
	}
}

void GameManager::Release()
{
}
