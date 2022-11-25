#include "KeyboardTest.h"
#include "Transform.h"
#include "Texture.h"
#include "SDLFramework.h"
#include "Player.h"
#include "State.h"

KeyboardTest::KeyboardTest()
{
	elapsedTime = 0.0f;
	frameRate = 0.5f;
	dir = 2;
}

KeyboardTest::~KeyboardTest()
{
}

void KeyboardTest::Update(float deltaTime)
{
	// 모든 키보드의 키 상태를 가져오는 함수
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	
	Texture* texture = gameObject->AddComponent<Texture>();

	texture->SetTexture(SDLFramework::Instance()->textures[16]);	//캐릭터의 텍스쳐
	texture->SetFrameRate(0.3f);
	texture->SetHorizonCount(3);
	texture->SetVerticalCount(1);
	texture->gameObject->transform->SetWidth(52);
	texture->SetAnimationActive(true);
	
	if (currentKeyStates[SDL_SCANCODE_UP])
	{
		gameObject->transform->Move(0, -5);
	}
	if (currentKeyStates[SDL_SCANCODE_DOWN])
	{
		gameObject->transform->Move(0, 5);
	}
	if (currentKeyStates[SDL_SCANCODE_LEFT])
	{
		texture->SetTexture(SDLFramework::Instance()->textures[17]);
		texture->SetFrameRate(0.1f);
		texture->SetHorizonCount(2);
		texture->SetVerticalCount(2);
		gameObject->transform->SetFlipMode(SDL_FLIP_NONE);
		dir = 1;
		gameObject->transform->Move(-5, 0);
		if (gameObject->transform->projRect.x <= 0)
		{
			gameObject->transform->projRect.x = 1280;

		}
	}
	if (currentKeyStates[SDL_SCANCODE_RIGHT])
	{
		texture->SetTexture(SDLFramework::Instance()->textures[17]);
		texture->SetFrameRate(0.1f);
		texture->SetHorizonCount(2);
		texture->SetVerticalCount(2);
		gameObject->transform->SetFlipMode(SDL_FLIP_HORIZONTAL);
		dir = 2;
		gameObject->transform->Move(5, 0);
		if (gameObject->transform->projRect.x + gameObject->transform->projRect.w >= 1280)
		{
			gameObject->transform->projRect.x = 0;
		}
	}
	if (currentKeyStates[SDL_SCANCODE_LCTRL])
	{
		texture->SetTexture(SDLFramework::Instance()->textures[19]);
		texture->SetFrameRate(0.25f);
		texture->SetHorizonCount(3);
		texture->SetVerticalCount(1);
		texture->gameObject->transform->SetWidth(76);
		gameObject->GetComponent<Player>()->directionState = dir;
		Player* player = gameObject->GetComponent<Player>();
		if (texture->GetFrameCount() == 0) {
			player->attackState = 1;
		}	
	}
	if (currentKeyStates[SDL_SCANCODE_A])
	{
		gameObject->GetComponent<State>()->SetHp(gameObject->GetComponent<State>()->GetHp() + 1);
	}
}