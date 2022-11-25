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
	int now, last = 0;			// now : ���� �����ӿ����� �ð��� ����� ����
								// last : ���� �����ӿ����� �ð��� ����� ����
	float deltaTime = 0.0f;		// ���� �����ӿ��� ���� ���� �����ӱ��� �ɸ� �ð�

	if (!SDLFramework::Instance()->Init())				// SDL �����ӿ�ũ �ʱ�ȭ
	{
		cout << "Failed to initialized!!" << endl;
		return 0;
	}

	GameManager::Instance()->Init();					// ���� ������ ������ �ʱ�ȭ

	bool quit = false;						// ���α׷� ������°� �Ǹ� true�� �ٲ� ����

	int frameTime = 1000;
	int elapsedTime = 0;

	// ���� �������� ó���� Event 
	SDL_Event e;

	while (!quit)
	{
		// Tick�� Time ���
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

			// Event �ڵ鷯 ȣ��
			SDLFramework::Instance()->HandleEvent(&e);
		}

		// ������Ʈ
		SDLFramework::Instance()->Update(deltaTime);

		// ����
		SDLFramework::Instance()->Render();
	}

	// ����
	SDLFramework::Instance()->Close();

	return 0;
}