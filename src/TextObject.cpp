#include "TextObject.h"

#include <cstring>

TextObject::TextObject()
{
	textSurface = NULL;
}

TextObject::~TextObject()
{
	TTF_CloseFont(font);
	font = NULL;
}

SDL_Texture* TextObject::getTextTexture()
{
	return texture;
}

void TextObject::WriteText(string text, TTF_Font* textFont, SDL_Color color, SDL_Renderer* renderer)
{
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
		font = NULL;
	}

	font = textFont;
	if (font == NULL)
	{
		cout << "Unable to open font! Error: " << TTF_GetError() << endl;
	}
	else
	{
		textSurface = TTF_RenderText_Solid(font, text.c_str(), color);

		if (textSurface == NULL)
		{
			cout << "Unable to load text! Error: " << TTF_GetError() << endl;
		}
		else
		{
			texture = SDL_CreateTextureFromSurface(renderer, textSurface);
			if (texture == NULL)
			{
				cout << "Unable to create texture from rendered text! SDL_ttf Error: " << TTF_GetError() << endl;
			}
			else
			{
				TTF_SizeText(font, text.c_str(), &(getSrc().w), &(getSrc().h));
			}
			SDL_FreeSurface(textSurface);
		}
	}
}

void TextObject::Render(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, getTextTexture(), &getSrc(), &getDest());
}
