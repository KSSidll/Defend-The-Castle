#ifndef USER_INTERFACE_WIN_MENU_H_
#define USER_INTERFACE_WIN_MENU_H_

#include "../../Game.h"
#include "../../Managers/FontManager.h"
#include "../../Objects/SceneObject.h"
#include "../Components/LabeledButton.h"
#include <deque>

class WinMenu
{
  private:
	std::deque<LabeledButton> buttons;
	SceneObject background;
	UILabel label;

	SDL_Rect saveButtonPos = { 156, 334, 200, 100 };
	SDL_Rect shopButtonPos = { 412, 334, 200, 100 };
	SDL_Rect nextLevelButtonPos = { 668, 334, 200, 100 };

  public:
	WinMenu ();
	~WinMenu ();

	WinMenu (SDL_Renderer *renderer, TextureManager *textureManager,
	         FontManager *fontManager, Game *game);

	void Render () const;
	void HandleEvents (SDL_Event *event);
};

#endif // USER_INTERFACE_WIN_MENU_H_