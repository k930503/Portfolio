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
	// transform�� ��ġ�� ���� collisionRect�� ���� ������ �ݴϴ�.
	collisionRect.x = gameObject->transform->projRect.x;
	collisionRect.y = gameObject->transform->projRect.y;
	collisionRect.w = gameObject->transform->projRect.w;
	collisionRect.h = gameObject->transform->projRect.h;

	// �θ� Ŭ������ Update�� ȣ�� : ���� �浹üũ�� �� �κ��� ���ֱ� ����
	Collider::Update(deltaTime);
}

bool RectangleCollider::isCollision(Collider* other)
{
	RectangleCollider* rCollider = dynamic_cast<RectangleCollider*>(other);
	CircleCollider*	   cCollider = dynamic_cast<CircleCollider*>(other);

	// other �� RectiagleCollider �� ��
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

	// other �� CircleCollider �� ��
	else if (cCollider != NULL)
	{

	}
	return false;
}