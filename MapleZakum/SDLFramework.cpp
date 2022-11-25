#include <iostream>
#include <algorithm>
#include "SDLFramework.h"

using namespace std;

void SDLFramework::AddGameObject(SDLGameObject * obj)
{
	gameObjects.push_back(obj);
}

void SDLFramework::RemoveGameObject(SDLGameObject * obj)
{
	list<SDLGameObject*>::iterator iter = std::find(
		gameObjects.begin(), gameObjects.end(), obj);
	if(iter != gameObjects.end())
		gameObjects.erase(iter);
}

void SDLFramework::AddCollideGameObject(SDLGameObject * obj)
{
	collideObjects.push_back(obj);
}

void SDLFramework::RemoveCollideGameObject(SDLGameObject * obj)
{
	list<SDLGameObject*>::iterator iter = std::find(
		collideObjects.begin(), collideObjects.end(), obj);
	if (iter != collideObjects.end())
		collideObjects.erase(iter);
}
SDLGameObject* SDLFramework::GetObject(string key) {
	map<string, SDLGameObject*>::iterator iter = collideObj.find(key);
	if (iter != collideObj.end())
	{
		return iter->second;
	}

	return NULL;
}

SDLFramework::SDLFramework()
{
}


SDLFramework::~SDLFramework()
{
}

bool SDLFramework::Init()
{
	bool success = true;
	//SDL 초기화
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)		// SDL 초기화 실패시
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else										// 초기화 성공시
	{
		//윈도우 생성
		window = SDL_CreateWindow(
			"SDL Tutorial",    //타이틀
			SDL_WINDOWPOS_UNDEFINED,  //x좌표
			SDL_WINDOWPOS_UNDEFINED,  //y좌표
			SCREEN_WIDTH,     //화면너비
			SCREEN_HEIGHT,     //화면높이
			SDL_WINDOW_SHOWN   //창 보이기
		);

		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create Renderer for Window
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

			if (renderer == NULL)
			{
				printf("Renderer Could not be created! SDL_Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				if (TTF_Init() == -1)
				{
					cout << "SDL_ttf could not initialize! SDL_ttf Error : " << TTF_GetError() << endl;
					success = false;
				}

				// 백그라운드 색 채우기
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					cout << "SDL_Image Could not initialize! SDL_Error : " << SDL_GetError() << endl;
					success = false;
				}
			}
		}
	}

	return success;
}

void SDLFramework::HandleEvent(SDL_Event* e)
{
	for (auto object : gameObjects)
	{
		object->HandleEvent(e);
	}
}

void SDLFramework::Update(float deltaTime)
{
	// Event 관련 처리 및 게임 오브젝트 Update
	for (auto object : gameObjects)
	{
		object->Update(deltaTime);
	}
}

void SDLFramework::Render()
{
	// 렌더러가 제대로 초기화 된경우에만 렌더
	if (renderer != NULL)
	{
		// 현재 백버퍼 (: 이전 프레임의 프론트버퍼)를 깨끗히 한다
		SDL_RenderClear(renderer);

		// 각 GameObject Render
		for (auto object : gameObjects)
		{
			object->Render();
		}

		// UpdateScreen : 백 버퍼와 프론트 버퍼를 스왑하여 업데이트 된 화면을 보여준다. 
		SDL_RenderPresent(renderer);
	}
}

void SDLFramework::Close()
{
	// 게임 오브젝트들 해제
	for (auto object : gameObjects)
	{
		delete object;
	}
	gameObjects.clear();

	// 폰트 파기
	for (auto font : fonts)
	{
		TTF_CloseFont(font);
	}
	fonts.clear();

	// 렌더러 파기
	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	//창 파괴
	SDL_DestroyWindow(window);
	window = NULL;

	//SDL 하위시스템 끝내기
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void SDLFramework::RegisterFont(string filePath, int fontSize)
{
	TTF_Font* font = TTF_OpenFont(filePath.c_str(), fontSize);
	if (font == NULL)
	{
		cout << "Failed to load Diablo font! SDL_ttf Error : " << TTF_GetError() << endl;
	}
	else
	{
		fonts.push_back(font);
	}
}