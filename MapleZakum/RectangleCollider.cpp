#include "RectangleCollider.h"
#include "CircleCollider.h"
#include "Transform.h"

RectangleCollider::RectangleCollider()
{
}

RectangleCollider::~RectangleCollider()
{
}

void RectangleCollider::Init()
{
	collisionRect = gameObject->transform->projRect;
}

void RectangleCollider::Update(float deltaTime)
{
	// transform의 위치에 따라 collisionRect도 같이 움직여 줍니다.
	collisionRect.x = gameObject->transform->projRect.x;
	collisionRect.y = gameObject->transform->projRect.y;
	collisionRect.w = gameObject->transform->projRect.w;
	collisionRect.h = gameObject->transform->projRect.h;

	// 부모 클래스의 Update도 호출 : 실제 충돌체크는 이 부분이 해주기 때문
	Collider::Update(deltaTime);
}

bool RectangleCollider::isCollision(Collider* other)
{
	RectangleCollider* rCollider = dynamic_cast<RectangleCollider*>(other);
	CircleCollider*	   cCollider = dynamic_cast<CircleCollider*>(other);

	// other 가 RectiagleCollider 일 때
	if (rCollider != NULL)
	{
		int left1 = collisionRect.x;
		int right1 = left1 + collisionRect.w;
		int top1 = collisionRect.y;
		int bottom1 = top1 + collisionRect.h;

		int left2 = rCollider->collisionRect.x;
		int right2 = left2 + rCollider->collisionRect.w;
		int top2 = rCollider->collisionRect.y;
		int bottom2 = top2 + rCollider->collisionRect.h;

		if( right1 <= left2 || left1 >= right2 ||
			top1 >= bottom2 || bottom1 <= top2 )
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	// other 가 CircleCollider 일 때
	else if (cCollider != NULL)
	{

	}
	return false;
}