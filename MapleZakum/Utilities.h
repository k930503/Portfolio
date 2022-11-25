#pragma once
#include <iostream>
#include <string>
#include "include\SDL.h"
#include "include\SDL_image.h"
#include "include\SDL_ttf.h"

using namespace std;

class Utilities
{
public:

	// 별도로 색을 정해주지 않을 시 255 0 255로 채워주기
	static SDL_Texture* LoadTexture(SDL_Renderer* renderer, string filePath, Uint8 cr = NULL, Uint8 cg = NULL, Uint8 cb = NULL)
	{
		SDL_Color* keyColor = new SDL_Color();

		keyColor->r = cr;
		keyColor->g = cg;
		keyColor->b = cb;

		if (cr == NULL && cg == NULL && cb == NULL)
		{
			keyColor = new SDL_Color();
			keyColor->r = 255; keyColor->g = 0; keyColor->b = 255;
		}

		// final Texture
		SDL_Texture* newTexture = NULL;

		// 이미지를 매개변수 filePath로 부터 로드
		SDL_Surface* surface = NULL; // 로드를 해서 바로 담을 Surface

		surface = IMG_Load(filePath.c_str()); // surface 에 로드

		if (surface == NULL)
		{
			cout << "Unable to load image " << filePath << "SDL_Error : " << SDL_GetError() << endl;
		}
		else
		{
			SDL_SetColorKey(
				surface,
				SDL_TRUE,
				SDL_MapRGB(surface->format, keyColor->r, keyColor->g, keyColor->b)
			);

			// 텍스처를 Surface 픽셀들로 부터 생성
			newTexture = SDL_CreateTextureFromSurface(renderer, surface);
			if (newTexture == NULL)
			{
				cout << "Unable to create texture from " << filePath << "SDL_Error : " << SDL_GetError() << endl;
			}

			// 필요없는 SDL_Surface* 를 해제
			SDL_FreeSurface(surface);
		}

		if (keyColor != NULL)
			delete keyColor;

		return newTexture;
	}

	static SDL_Texture* LoadTextureFromFont(SDL_Renderer* renderer, TTF_Font* font, string textureText, SDL_Color* textColor = NULL)
	{
		SDL_Texture* texture = NULL;

		SDL_Color color;
		if (textColor == NULL)
		{
			color.r = 0x00; color.g = 0x00; color.b = 0x00; color.a = 0xFF;
		}
		else
		{
			color = *textColor;
		}

		SDL_Surface* surface = TTF_RenderText_Solid(font, textureText.c_str(), color);

		if (surface == NULL)
		{
			cout << "Unable to render text surface! SDL_ttf Error : " << TTF_GetError() << endl;
		}
		else
		{
			texture = SDL_CreateTextureFromSurface(renderer, surface);

			if (texture == NULL)
			{
				cout << "Unable to create texture from rendered text! SDL Error : " << SDL_GetError() << endl;
			}

			SDL_FreeSurface(surface);
		}

		return texture;
	}


public:
	Utilities();
	~Utilities();
};

