#pragma once
#include "include\SDL.h"
#include "include\SDL_image.h"
#include "Component.h"

class Texture;

class Transform :
	public Component
{
public:
	double				angle;			// �ð���������� ȸ�� ����
	double				rotate;
	double				range;

	string				name;
	// Transform Component
	SDL_Rect			clipRect;		// Render�ÿ� Texture�� ���� Ŭ���� �� ����
	SDL_Rect			projRect;		// ���� ��ġ�� ũ�⸦ ��Ÿ���� ����
	SDL_Point			centerPoint;	// ȸ�� ��ų ���� ��ġ
	SDL_RendererFlip	flipMode;		// flip ��ų ���

public:
	Transform();
	~Transform();

	void Init();
	void Update(float deltaTime);

	// member Functions
	void SetPosition(int x, int y);
	void SetClipRect(int x, int y, int width, int height);
	void SetWidth(int width);
	void SetHeight(int height);
	void SetAngle(double _angle);
	void SetFlipMode(SDL_RendererFlip flip);
	void SetCenterPoint(int x, int y);
	void SetRotate(double _rotate);
	void AccumulateRotate(double _r, double _rv);
	double GetRotate();
	double GetRange();

	void Move(int x, int y);
	int GetxPos() { return projRect.x; }
};

