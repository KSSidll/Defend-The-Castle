#ifndef USER_INTERFACE_WIN_MENU_H_

#define USER_INTERFACE_WIN_MENU_H_

#include "Button.h"
#include <SDL2/SDL.h>
#include <deque>

struct LabeledButton;

class Button;
class Game;
class UILabel;
class SceneObject;
class TextureManager;

class WinMenu
{
  private:
	Game *game;
	SDL_Renderer *renderer;

	std::deque<LabeledButton> buttons;
	SceneObject *background;
	UILabel *label;

	SDL_Rect saveButtonPos = { 156, 334, 200, 100 };
	SDL_Rect shopButtonPos = { 412, 334, 200, 100 };
	SDL_Rect nextLevelButtonPos = { 668, 334, 200, 100 };

  public:
	WinMenu ();
	~WinMenu ();

	WinMenu (SDL_Renderer *renderer, Game *game,
	         TextureManager *textureManager);

	void Render ();
	void HandleEvents (SDL_Event *event);
};

#endif // USER_INTERFACE_WIN_MENU_H_