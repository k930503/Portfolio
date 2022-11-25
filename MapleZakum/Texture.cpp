#include "Texture.h"
#include "Transform.h"
#include "SDLFramework.h"
#include <iostream>
Texture::Texture()
{
	elapsedTime = 0.0f;
	frameCount = 0;
	
}

Texture::~Texture()
{
}

void Texture::Update(float deltaTime)
{
	Transform* transform = gameObject->transform;
	if (isActiveAnimation)
	{
		elapsedTime += deltaTime;
		if (elapsedTime > frameRate)
		{
			frameCount++;
			if (frameCount >= horizonCount * verticalCount)
				frameCount = 0;

			elapsedTime = 0.0f;
		}
	}

	unsigned int sizeHorizontal = textureWidth / horizonCount;
	unsigned int sizeVertical = textureHeight / verticalCount;

	unsigned int xPos, yPos;
	xPos = yPos = 0;

	if(horizonCount > 1)
		xPos = frameCount % horizonCount;
	if(verticalCount > 1)
		yPos = frameCount / horizonCount;

	transform->SetClipRect(xPos * sizeHorizontal, yPos * sizeVertical, sizeHorizontal, sizeVertical);
}

void Texture::SetTexture(SDL_Texture* _tex)
{
	texture = _tex;

	SDL_QueryTexture(texture, NULL, NULL,
		&(textureWidth), &(textureHeight));
}

void Texture::SetBlendMode(SDL_BlendMode blendMode)
{
	SDL_SetTextureBlendMode(GetTexture(), blendMode);
}

void Texture::SetAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(GetTexture(), alpha);
}
void Texture::SetFrameCount(unsigned int _frameCount)
{
	frameCount = _frameCount;
}
unsigned int Texture::GetFrameCount()
{
	return frameCount;
}

void Texture::Render()
{
	Transform* transform = gameObject->transform;
	SDL_RenderCopyEx(
		SDLFramework::Instance()->GetRenderer(),
		texture,
		&transform->clipRect,
		&transform->projRect,
		transform->angle,
		&transform->centerPoint,
		transform->flipMode
		);
	//std::cout << transform->angle << std::endl;
}
