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
	static SDLFramework* instance;			// singleton 인스턴스
	SDL_Window* window;						// Window 객체 포인터
	SDL_Renderer* renderer;					// Renderer   "
	vector<TTF_Font*> fonts;				// 미리 로딩해서 쓸 폰트 목록
	list<SDLGameObject*> gameObjects;		// 현재 돌아가고 있는 모든 GameObject
	

public:
	static SDLFramework* Instance()			// Framework 인스턴스 가져올 함수
	{
		if (instance == NULL)
		{
			instance = new SDLFramework();
		}
		return instance;
	}
	list<SDLGameObject*> collideObjects;

	map<string, SDLGameObject*> collideObj;
	vector<SDL_Texture*> textures;		// 미리 로딩해서 쓸 텍스쳐 목록, map으로 변경 할 예정

	SDL_Window* GetWindow() { return window; }			// Window Getter
	SDL_Renderer* GetRenderer() { return renderer; }	// Renderer Getter
	TTF_Font* GetFont(unsigned int index) { return fonts[index]; }	// Font Getter;

	void AddGameObject(SDLGameObject* obj);				// 게임 오브젝트 등록
	void RemoveGameObject(SDLGameObject* obj);			// 게임 오브젝트 제거
	list<SDLGameObject*> GetObjectList() {
		return gameObjects;
	}

	void AddCollideGameObject(SDLGameObject* obj);				// 게임 오브젝트 등록
	void RemoveCollideGameObject(SDLGameObject* obj);			// 게임 오브젝트 제거
	list<SDLGameObject*> GetCollideObjectList() {
		return collideObjects;
	}
	SDLGameObject* GetObject(string key);



	//화면크기
	const int SCREEN_WIDTH = WINDOWS_WIDTH;				// 화면 해상도
	const int SCREEN_HEIGHT = WINDOWS_HEIGHT;			// 화면 해상도

	SDLFramework();										// Framework 생성자
	~SDLFramework();

	bool Init();										// SDL 관련 초기화
	void HandleEvent(SDL_Event* e);						// Event를 Object의 각 Component에 전달할 함수
	void Update(float deltaTime);						// GameObjects Update
	void Render();										// GameObjects Render
	void Close();										// SDL 및 GameObjects 해제

	void RegisterFont(string filePath, int fontSize);	// 폰트 등록;
};

