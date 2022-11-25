#pragma once
#include <iostream>
#include <map>
#include <string>

class SDLGameObject;

using namespace std;

// 폰트 등록 열거형 키
enum RegisteredFont
{
	DiabloLight,
};

class GameManager
{
	// 역시 싱글턴으로
	static GameManager* instance;
	map<string, SDLGameObject*> contentObjects;

public:
	static GameManager* Instance()
	{
		if (instance == NULL)
		{
			instance = new GameManager();
		}
		return instance;
	}

	GameManager();
	~GameManager();

	// 최초 Objects (또는 Scene) 초기화
	void Init();			

	// 게임 컨텐츠 오브젝트를 Key를 통해 Framework로 등록
	void RegisterObject(string key, SDLGameObject* object);	

	SDLGameObject* GetObject(string key);

	// 키로 게임 오브젝트 제거
	void DestroyObject(string key);

	// 게임 종료시 해제 할 것들을 해제
	void Release();
};

