#pragma once
#include <vector>
#include <list>
#include <string>
#include <map>

#include "include\SDL.h"
#include "include\SDL_image.h"
#include "include\SDL_ttf.h"
#include "SDLGameObject.h"

using namespace std;

#define WINDOWS_WIDTH 1280
#define WINDOWS_HEIGHT 720

class SDLFramework
{
private:
	static SDLFramework* instance;			// singleton �ν��Ͻ�
	SDL_Window* window;						// Window ��ü ������
	SDL_Renderer* renderer;					// Renderer   "
	vector<TTF_Font*> fonts;				// �̸� �ε��ؼ� �� ��Ʈ ���
	list<SDLGameObject*> gameObjects;		// ���� ���ư��� �ִ� ��� GameObject
	

public:
	static SDLFramework* Instance()			// Framework �ν��Ͻ� ������ �Լ�
	{
		if (instance == NULL)
		{
			instance = new SDLFramework();
		}
		return instance;
	}
	list<SDLGameObject*> collideObjects;

	map<string, SDLGameObject*> collideObj;
	vector<SDL_Texture*> textures;		// �̸� �ε��ؼ� �� �ؽ��� ���, map���� ���� �� ����

	SDL_Window* GetWindow() { return window; }			// Window Getter
	SDL_Renderer* GetRenderer() { return renderer; }	// Renderer Getter
	TTF_Font* GetFont(unsigned int index) { return fonts[index]; }	// Font Getter;

	void AddGameObject(SDLGameObject* obj);				// ���� ������Ʈ ���
	void RemoveGameObject(SDLGameObject* obj);			// ���� ������Ʈ ����
	list<SDLGameObject*> GetObjectList() {
		return gameObjects;
	}

	void AddCollideGameObject(SDLGameObject* obj);				// ���� ������Ʈ ���
	void RemoveCollideGameObject(SDLGameObject* obj);			// ���� ������Ʈ ����
	list<SDLGameObject*> GetCollideObjectList() {
		return collideObjects;
	}
	SDLGameObject* GetObject(string key);



	//ȭ��ũ��
	const int SCREEN_WIDTH = WINDOWS_WIDTH;				// ȭ�� �ػ�
	const int SCREEN_HEIGHT = WINDOWS_HEIGHT;			// ȭ�� �ػ�

	SDLFramework();										// Framework ������
	~SDLFramework();

	bool Init();										// SDL ���� �ʱ�ȭ
	void HandleEvent(SDL_Event* e);						// Event�� Object�� �� Component�� ������ �Լ�
	void Update(float deltaTime);						// GameObjects Update
	void Render();										// GameObjects Render
	void Close();										// SDL �� GameObjects ����

	void RegisterFont(string filePath, int fontSize);	// ��Ʈ ���;
};

