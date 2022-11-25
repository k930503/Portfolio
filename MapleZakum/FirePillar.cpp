#include "FirePillar.h"
#include "Transform.h"
#include "Texture.h"

using namespace std;

void FirePillar::SetState(FirePillarState _state)
{
	state = _state;
	elapsedTime = 0.0f;
}

FirePillar::FirePillar()
{
}

FirePillar::FirePillar(const char* _name, SDLGameObject* _object)
{
	_object->name = _name;
}

FirePillar::~FirePillar()
{
}

void FirePillar::SetPosition(int x, int y)
{
	areaPreview->transform->SetPosition(x, y);
	areaPreview->GetComponent<Texture>()->SetFrameCount(0);
	areaPreview->GetComponent<Texture>()->Update(0);

	dropFire->transform->SetPosition(x + 18, 0);
	dropFire->GetComponent<Texture>()->SetFrameCount(0);
	dropFire->GetComponent<Texture>()->Update(0);

	destroyFire->transform->SetPosition(x, y);
	destroyFire->GetComponent<Texture>()->SetFrameCount(0);
	destroyFire->GetComponent<Texture>()->Update(0);
}

void FirePillar::Activate()
{
	gameObject->active = true;
	SetState(Alarm);
}

void FirePillar::DeActivate()
{
	gameObject->active = false;
}

void FirePillar::Update(float deltaTime)
{
	elapsedTime += deltaTime;

	switch (state)
	{
		case Alarm:

			areaPreview->Update(deltaTime);
			if (elapsedTime > durationAlarm)	// 불기둥 알림신호가 끝난후 불기둥발사상태로 바꿈
				SetState(Fire);
			break;

		case Fire:

			dropFire->active = true;
			(dropFire->transform->projRect.y) = (dropFire->transform->projRect.y) + 8;
			dropFire->Update(deltaTime);

			if (elapsedTime > durationFire)
			{
				SetState(Destroy);
				dropFire->active = false;
			}
			break;

		case Destroy:

			destroyFire->Update(deltaTime);
			if (elapsedTime > durationDestroy)
				DeActivate();
			break;
	}
}

void FirePillar::Render()
{
	switch (state)
	{
		case Alarm:
			areaPreview->Render();
			break;
		case Fire:
			dropFire->Render();
			break;
		case Destroy:
			destroyFire->Render();
			break;
	}
}

