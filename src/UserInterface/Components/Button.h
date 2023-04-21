#ifndef USER_INTERFACE_COMPONENTS_BUTTON_H_
#define USER_INTERFACE_COMPONENTS_BUTTON_H_

#include "../../Managers/TextureManager.h"
#include <SDL2/SDL.h>
#include <functional>

enum BUTTON_STATE
{
	MOUSE_OUT = 0,
	MOUSE_OVER = 1,
	MOUSE_DOWN = 2,
	MOUSE_UP = 3
};

class Button
{
  private:
	BUTTON_STATE BUTTON_STATE = MOUSE_OUT;

	SDL_Renderer *renderer;
	SDL_Rect rect;

	ButtonTextures *textures;

	std::function<void ()> callback;

  public:
	Button ();
	~Button ();

	Button (SDL_Renderer *renderer, ButtonTextures *textures, SDL_Rect rect);
	Button (SDL_Renderer *renderer, ButtonTextures *textures, SDL_Rect rect,
	        std::function<void ()> callback);

	void Render () const;
	bool HandleEvents (SDL_Event *event, bool callback_on_click = false);

	void Callback () const;
};

#endif // USER_INTERFACE_COMPONENTS_BUTTON_H_