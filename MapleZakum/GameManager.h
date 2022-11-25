#pragma once
#include <iostream>
#include <map>
#include <string>

class SDLGameObject;

using namespace std;

// ��Ʈ ��� ������ Ű
enum RegisteredFont
{
	DiabloLight,
};

class GameManager
{
	// ���� �̱�������
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

	// ���� Objects (�Ǵ� Scene) �ʱ�ȭ
	void Init();			

	// ���� ������ ������Ʈ�� Key�� ���� Framework�� ���
	void RegisterObject(string key, SDLGameObject* object);	

	SDLGameObject* GetObject(string key);

	// Ű�� ���� ������Ʈ ����
	void DestroyObject(string key);

	// ���� ����� ���� �� �͵��� ����
	void Release();
};

