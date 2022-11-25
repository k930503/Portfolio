#include "CircleCollider.h"
#include "RectangleCollider.h"
#include "Transform.h"
#include <cmath>

bool IsPointInCircle(int px, int py, CircleCollider* circle)
{
	int xDelta = circle->centerX - px;
	int yDelta = circle->centerY - py;

	float distance = sqrtf((float)(xDelta * xDelta + yDelta * yDelta));

	if (circle->radius >= (int)distance)
		return true;
	else
		return false;
}

CircleCollider::CircleCollider()
{
}

CircleCollider::~CircleCollider()
{
}

void CircleCollider::Init()
{
	int x = gameObject->transform->projRect.x;
	int y = gameObject->transform->projRect.y;
	int w = gameObject->transform->projRect.w;
	int h = gameObject->transform->projRect.h;

	centerX = x + (w / 2);
	centerY = y + (h / 2);

	int xPow = (w / 2) * (w / 2);
	int yPow = (h / 2) * (h / 2);

	float distance =
		sqrtf((float)(xPow + yPow));

	radius = (int)distance;
}

void CircleCollider::Update(float deltaTime)
{
	UpdateCenter();

	Collider::Update(deltaTime);
}

void CircleCollider::UpdateCenter()
{
	int x = gameObject->transform->projRect.x;
	int y = gameObject->transform->projRect.y;
	int w = gameObject->transform->projRect.w;
	int h = gameObject->transform->projRect.h;

	centerX = x + (w / 2);
	centerY = y + (h / 2);
}

bool CircleCollider::isCollision(Collider * other)
{
	RectangleCollider* rCollider = dynamic_cast<RectangleCollider*>(other);
	CircleCollider* cCollider = dynamic_cast<CircleCollider*>(other);

	if (cCollider != NULL)
	{
		float distance = sqrt(powf((float)(cCollider->centerX - centerX), 2) +
							  powf((float)(cCollider->centerY - centerY), 2));

		if ((int)distance <= radius + cCollider->radius)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (rCollider != NULL)
	{
		SDL_Rect r = rCollider->collisionRect;

		if ( (r.x <= centerX && centerX <= r.x + r.w) ||
			 (r.y <= centerY && centerY <= r.y + r.h) )
		{
			// 원의 반지름 만큼 확장된 사각형의 각 x, y 좌표를 구함
			int left = r.x - radius;
			int top = r.y - radius;
			int right = r.x + r.w + radius;
			int bottom = r.y + r.h + radius;

			if ( (left < centerX && centerX < right) &&
				 (top < centerY && centerY < bottom) )
			{
				return true;
			}
		}
		else
		{
			if (IsPointInCircle(r.x, r.y, this))
				return true;

			if (IsPointInCircle(r.x + r.w, r.y, this))
				return true;

			if (IsPointInCircle(r.x, r.y + r.h, this))
				return true;

			if (IsPointInCircle(r.x + r.w, r.y + r.h, this))
				return true;
		}
	}
	return false;
}