#include <iostream>
#include <string>
#include <vector>
#include<Windows.h>
#include <MMSystem.h>
#pragma comment(lib,"Winmm.lib")

#include "include\SDL.h"
#include "include\SDL_image.h"
#include "include\SDL_ttf.h"
#include "SDLGameObject.h"
#include "SDLFramework.h"
#include "Transform.h"
#include "Texture.h"
#include "Utilities.h"

#include "GameManager.h"

using namespace std;

SDLFramework* SDLFramework::instance = NULL;
GameManager*  GameManager::instance = NULL;

int main(int argc, char* args[])
{
	sndPlaySoundA("./Media/bgm.wav", SND_ASYNC | SND_NODEFAULT);
	int now, last = 0;			// now : 현재 프레임에서의 시각을 기록할 변수
								// last : 이전 프레임에서의 시각을 기록한 변수
	float deltaTime = 0.0f;		// 이전 프레임에서 부터 현재 프레임까지 걸린 시간

	if (!SDLFramework::Instance()->Init())				// SDL 프레임워크 초기화
	{
		cout << "Failed to initialized!!" << endl;
		return 0;
	}

	GameManager::Instance()->Init();					// 게임 컨텐츠 관리자 초기화

	bool quit = false;						// 프로그램 종료상태가 되면 true로 바뀔 변수

	int frameTime = 1000;
	int elapsedTime = 0;

	// 메인 루프에서 처리할 Event 
	SDL_Event e;

	while (!quit)
	{
		// Tick당 Time 계산
		now = SDL_GetTicks();
		if (now > last)
		{
			elapsedTime += now - last;
			deltaTime = ((float)(now - last)) / 1000.0f;
			last = now;
		}

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

			// Event 핸들러 호출
			SDLFramework::Instance()->HandleEvent(&e);
		}

		// 업데이트
		SDLFramework::Instance()->Update(deltaTime);

		// 렌더
		SDLFramework::Instance()->Render();
	}

	// 해제
	SDLFramework::Instance()->Close();

	return 0;
}