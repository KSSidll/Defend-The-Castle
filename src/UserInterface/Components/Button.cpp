#include "Button.h"

Button::Button ()
{
	renderer = nullptr;
	textures = nullptr;
}

Button::~Button ()
{
	textures = nullptr;
	renderer = nullptr;
}

Button::Button (SDL_Renderer *renderer, ButtonTextures *textures,
                SDL_Rect rect)
	: Button::Button ()
{
	this->rect.x = rect.x;
	this->rect.y = rect.y;
	this->rect.w = rect.w;
	this->rect.h = rect.h;

	this->renderer = renderer;
	this->textures = textures;
}

Button::Button (SDL_Renderer *renderer, ButtonTextures *textures,
                SDL_Rect rect, std::function<void ()> callback)
	: Button (renderer, textures, rect)
{
	this->callback = callback;
}

void
Button::Render () const
{

	switch (BUTTON_STATE)
	{
	case MOUSE_OUT:
		SDL_RenderCopy (renderer, textures->none, NULL, &rect);
		break;

	case MOUSE_OVER:
		SDL_RenderCopy (renderer, textures->over, NULL, &rect);
		break;

	case MOUSE_DOWN:
		SDL_RenderCopy (renderer, textures->down, NULL, &rect);
		break;

	case MOUSE_UP:
		SDL_RenderCopy (renderer, textures->none, NULL, &rect);
		break;
	}
}

bool
Button::HandleEvents (SDL_Event *event, bool callback_on_click)
{
	if (event->type == SDL_MOUSEMOTION || event->type == SDL_MOUSEBUTTONDOWN
	    || event->type == SDL_MOUSEBUTTONUP)
	{
		int x, y;
		bool inside = true;
		SDL_GetMouseState (&x, &y);

		if (x < rect.x)
			inside = false;
		else if (x > rect.x + rect.w)
			inside = false;
		else if (y < rect.y)
			inside = false;
		else if (y > rect.y + rect.h)
			inside = false;

		if (!inside)
			BUTTON_STATE = MOUSE_OUT;
		else if (BUTTON_STATE == MOUSE_OUT)
			BUTTON_STATE = MOUSE_OVER;
	}

	if (event->type == SDL_MOUSEBUTTONDOWN)
	{
		if (BUTTON_STATE == MOUSE_OVER)
			BUTTON_STATE = MOUSE_DOWN;
	}

	if (event->type == SDL_MOUSEBUTTONUP)
	{
		if (BUTTON_STATE == MOUSE_DOWN)
			BUTTON_STATE = MOUSE_UP;
	}

	if (BUTTON_STATE == MOUSE_UP)
	{
		BUTTON_STATE = MOUSE_OVER;

		if (callback_on_click)
		{
			Callback ();
		}

		return true;
	}
	return false;
}

void
Button::Callback () const
{
	callback ();
}