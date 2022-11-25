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
	//SDL �ʱ�ȭ
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)		// SDL �ʱ�ȭ ���н�
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else										// �ʱ�ȭ ������
	{
		//������ ����
		window = SDL_CreateWindow(
			"SDL Tutorial",    //Ÿ��Ʋ
			SDL_WINDOWPOS_UNDEFINED,  //x��ǥ
			SDL_WINDOWPOS_UNDEFINED,  //y��ǥ
			SCREEN_WIDTH,     //ȭ��ʺ�
			SCREEN_HEIGHT,     //ȭ�����
			SDL_WINDOW_SHOWN   //â ���̱�
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

				// ��׶��� �� ä���
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
	// Event ���� ó�� �� ���� ������Ʈ Update
	for (auto object : gameObjects)
	{
		object->Update(deltaTime);
	}
}

void SDLFramework::Render()
{
	// �������� ����� �ʱ�ȭ �Ȱ�쿡�� ����
	if (renderer != NULL)
	{
		// ���� ����� (: ���� �������� ����Ʈ����)�� ������ �Ѵ�
		SDL_RenderClear(renderer);

		// �� GameObject Render
		for (auto object : gameObjects)
		{
			object->Render();
		}

		// UpdateScreen : �� ���ۿ� ����Ʈ ���۸� �����Ͽ� ������Ʈ �� ȭ���� �����ش�. 
		SDL_RenderPresent(renderer);
	}
}

void SDLFramework::Close()
{
	// ���� ������Ʈ�� ����
	for (auto object : gameObjects)
	{
		delete object;
	}
	gameObjects.clear();

	// ��Ʈ �ı�
	for (auto font : fonts)
	{
		TTF_CloseFont(font);
	}
	fonts.clear();

	// ������ �ı�
	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	//â �ı�
	SDL_DestroyWindow(window);
	window = NULL;

	//SDL �����ý��� ������
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