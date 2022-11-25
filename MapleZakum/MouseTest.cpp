#include "MouseTest.h"
#include "Transform.h"
#include "Texture.h"

MouseTest::MouseTest()
{
}
MouseTest::~MouseTest()
{
}

void MouseTest::HandleEvent(SDL_Event* e)
{
	if (linkedTransform == NULL)
		return;

	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);

		bool inside = true;
		
		if ( x < linkedTransform->projRect.x || 
			 x > linkedTransform->projRect.x + linkedTransform->projRect.w || 
			 y < linkedTransform->projRect.y ||
			 y > linkedTransform->projRect.y + linkedTransform->projRect.h )
		{
			inside = false;
		}

		if (inside == false)
			return;

		Texture* tex = linkedTransform->gameObject->GetComponent<Texture>();
		if (tex == NULL)
			return;

		switch (e->type)
		{
		case SDL_MOUSEBUTTONDOWN:
			tex->SetAnimationActive(false);
			break;
		case SDL_MOUSEBUTTONUP:
			tex->SetAnimationActive(true);
			break;
		case SDL_MOUSEMOTION:
		default:
			break;
		}
	}
}
