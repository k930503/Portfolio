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
	// ���ӿ� �ʿ��� ������Ʈ �Ǵ� Scene ���� �ʱ� ��ġ �� ���

	// ��Ʈ �ε�
	SDLFramework::Instance()->RegisterFont("./Media/Font/DiabloLight.ttf", 48);

	SDL_Texture* tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/background.png");  // ��� 0
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
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/arm8.png", 0xFF, 0xFF, 0xFF); // �� 8
	SDLFramework::Instance()->textures.push_back(tex);


	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/zakumBody1.png");  // �� 9
	SDLFramework::Instance()->textures.push_back(tex);

	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/firepillarCue.png", 0xFF, 0xFF, 0xFF);  // �ұ�� 10
	SDLFramework::Instance()->textures.push_back(tex);

	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/fireDrop.png", 0xFF, 0xFF, 0xFF);
	SDLFramework::Instance()->textures.push_back(tex);

	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/destroyFire.png", 255, 255, 255);
	SDLFramework::Instance()->textures.push_back(tex);

	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/thunder.png", 255, 255, 255);  // ���� 13
	SDLFramework::Instance()->textures.push_back(tex);

	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/secondPhase.png", 255, 0, 255); // ��2 14
	SDLFramework::Instance()->textures.push_back(tex);

	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/zakumDie.png");  // �� �������°� 15
	SDLFramework::Instance()->textures.push_back(tex);

	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/stopMotion.png");  // ������� 16
	SDLFramework::Instance()->textures.push_back(tex);

	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/moveMotion.png");  // �����Ӹ�� 17
	SDLFramework::Instance()->textures.push_back(tex);

	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/jumpMotion.png");  // ������� 18
	SDLFramework::Instance()->textures.push_back(tex);

	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/attackMotion.png");  // ���� ��� 19
	SDLFramework::Instance()->textures.push_back(tex);

	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/Dart.png");  // ǥâ 20
	SDLFramework::Instance()->textures.push_back(tex);

	// UI 21~
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/statusgrd.png");  // ��� 0
	SDLFramework::Instance()->textures.push_back(tex);

	// ������ 22~32
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/LvKinesis.png"); // ������
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/lvNumber0.png"); // ����0
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/lvNumber1.png"); // ����1
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/lvNumber2.png"); // ����2
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/lvNumber3.png"); // ����3
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/lvNumber4.png"); // ����4
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/lvNumber5.png"); // ����5
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/lvNumber6.png"); // ����6
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/lvNumber7.png"); // ����7
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/lvNumber8.png"); // ����8
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/lvNumber9.png"); // ����9
	SDLFramework::Instance()->textures.push_back(tex);

	// ä�ù� 33~37
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/chatBase.png"); // ������
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/chatAll.png"); // ������
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/chatEnter.png"); // ������
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/BtChat.png"); // ������
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/BtClaim.png"); // ������
	SDLFramework::Instance()->textures.push_back(tex);

	// ���¹� 38
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/UI/gaugeBackgrd.png"); // ������
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

	// ��Ÿ status â 57 ~ 71
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

	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/creep.png");  // ���� 70
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/creep_hit.png");  // ���� ���� 71
	SDLFramework::Instance()->textures.push_back(tex);
	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/creep_die.png");  // ���� �ְ� 72
	SDLFramework::Instance()->textures.push_back(tex);

	tex = Utilities::LoadTexture(SDLFramework::Instance()->GetRenderer(), "./Media/cap.png");  // ���� �ְ� 72
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

	// �������
	obj = new SDLGameObject("Zakum");
	obj->AddComponent<Zakum>();
	RegisterObject(obj->name, obj);

	// UI����
	obj = new SDLGameObject("Ui");
	obj->AddComponent<UI>();
	obj->AddComponent<UIState>();
	RegisterObject(obj->name, obj);


	// �÷��̾� ������Ʈ ����
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

	// ũ�� ��ȯ
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
		cout << key << " : �̹� ��ϵ� Ű�� �ֽ��ϴ�. Object ��Ͽ� ���� �Ͽ����ϴ�."
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
