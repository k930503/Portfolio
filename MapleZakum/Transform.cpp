#include <math.h>
#include <iostream>

#include "Transform.h"
#include "Texture.h"

Transform::Transform()
{
	angle = 0.0f;
	rotate = 0.0f;
	range = 0.0f;

	// 위치 및 크기 초기화
	clipRect.x = 0; clipRect.y = 0;
	projRect.x = 0; projRect.y = 0;
	projRect.w = clipRect.w;
	projRect.h = clipRect.h;

	flipMode		= SDL_FLIP_NONE;
	centerPoint.x	= 0; centerPoint.y = 0;
}

Transform::~Transform()
{
}

void Transform::Init()
{
}

void Transform::Update(float deltaTime)
{
}

void Transform::SetPosition(int x, int y)
{
	projRect.x = x; projRect.y = y;
}

void Transform::SetClipRect(int x, int y, int width, int height)
{
	clipRect.x = x; clipRect.y = y; clipRect.w = width; clipRect.h = height;
}

void Transform::SetWidth(int width)
{
	projRect.w = width;
}

void Transform::SetHeight(int height)
{
	projRect.h = height;
}

void Transform::SetAngle(double _angle)
{
	angle = _angle;
}

double Transform::GetRange()
{
	return range;
}

void Transform::SetRotate(double _rotate)
{
	rotate = _rotate;
}

double Transform::GetRotate()
{
	return rotate;
}

void Transform::AccumulateRotate(double _r, double _rv)
{
	rotate = _r + _rv;
}
void Transform::SetFlipMode(SDL_RendererFlip flip)
{
	flipMode = flip;
}

void Transform::SetCenterPoint(int x, int y)
{
	centerPoint.x = x;
	centerPoint.y = y;
}

void Transform::Move(int x, int y)
{
	projRect.x += x; 
	projRect.y += y;
}
