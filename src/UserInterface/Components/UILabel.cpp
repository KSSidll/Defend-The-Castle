#include "UILabel.h"
#include <algorithm>

UILabel::UILabel ()
{
	renderer = nullptr;
	font = nullptr;
	texture = nullptr;
}

UILabel::~UILabel ()
{
	texture = nullptr;
	font = nullptr;
	renderer = nullptr;
}

UILabel::UILabel (SDL_Renderer *renderer, int xPos, int yPos, TTF_Font *font,
                  std::string text, SDL_Color color)
	: UILabel::UILabel ()
{
	this->renderer = renderer;
	this->font = font;

	this->color = color;
	this->text = text;

	org_refPos.x = position.x = xPos;
	org_refPos.y = position.y = yPos;

	TTF_SizeText (font, text.c_str (), &position.w, &position.h);

	SDL_Surface *surfaceText = TTF_RenderText_Blended_Wrapped (
		font, text.c_str (), color, position.w);
	texture = SDL_CreateTextureFromSurface (renderer, surfaceText);
	SDL_FreeSurface (surfaceText);

	SDL_QueryTexture (texture, NULL, NULL, &position.w, &position.h);
}

UILabel::UILabel (SDL_Renderer *renderer, int xPos, int yPos, TTF_Font *font,
                  std::string text, SDL_Color color, int labelWidth)
	: UILabel (renderer, xPos, yPos, font, text, color)
{
	if (labelWidth > 0)
	{
		org_refPos.w = labelWidth;
		position.x += (labelWidth - position.w) / 2;
		wCentered = true;
	}
}

UILabel::UILabel (SDL_Renderer *renderer, int xPos, int yPos, TTF_Font *font,
                  std::string text, SDL_Color color, int labelWidth,
                  int labelHeight)
	: UILabel (renderer, xPos, yPos, font, text, color, labelWidth)
{
	if (labelHeight > 0)
	{
		org_refPos.h = labelHeight;
		position.y += (labelHeight - position.h) / 2;
		hCentered = true;
	}
}

void
UILabel::ChangeText (const char *text)
{
	position.x = org_refPos.x;
	position.y = org_refPos.y;

	TTF_SizeText (font, text, &position.w, &position.h);

	SDL_Surface *surfaceText
		= TTF_RenderText_Blended_Wrapped (font, text, color, position.w);
	texture = SDL_CreateTextureFromSurface (renderer, surfaceText);
	SDL_FreeSurface (surfaceText);

	SDL_QueryTexture (texture, NULL, NULL, &position.w, &position.h);

	if (wCentered)
	{
		position.x += (org_refPos.w - position.w) / 2;
	}

	if (hCentered)
	{
		position.y += (org_refPos.h - position.h) / 2;
	}
}

void
UILabel::Render () const
{
	SDL_RenderCopy (renderer, texture, NULL, &position);
}

SDL_Rect
UILabel::GetPosition () const
{
	return position;
};