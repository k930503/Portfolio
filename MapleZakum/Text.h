#pragma once
#include "Texture.h"
#include "include\SDL_ttf.h"

class Text :
	public Texture
{
private:
	TTF_Font* font = NULL;
public:
	Text();
	~Text();

	void SetText(int fontIndex, string _text, SDL_Color* color = NULL);
};

