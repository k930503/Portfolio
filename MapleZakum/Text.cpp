#include "Text.h"
#include "SDLFramework.h"
#include "Utilities.h"

Text::Text()
{
}

Text::~Text()
{
}

void Text::SetText(int fontIndex, string _text, SDL_Color * color)
{
	font = SDLFramework::Instance()->GetFont(fontIndex);
	SDL_Renderer* renderer = SDLFramework::Instance()->GetRenderer();
	texture = Utilities::LoadTextureFromFont(renderer, font, _text, color);
	SDL_QueryTexture(texture, NULL, NULL,
		&(textureWidth), &(textureHeight));
}
