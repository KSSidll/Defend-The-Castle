#ifndef USER_INTERFACE_MAIN_MENU_H_
#define USER_INTERFACE_MAIN_MENU_H_

#include "../../Game.h"
#include "../../Managers/FontManager.h"
#include "../../Objects/SceneObject.h"
#include "../Components/LabeledButton.h"
#include <deque>

class MainMenu
{
  private:
	std::deque<LabeledButton> buttons;
	SceneObject background;

	UILabel mainMenuLabel;

	SDL_Rect newGameButtonPos = { 362, 200, 300, 150 };
	SDL_Rect continueButtonPos = { 362, 400, 300, 150 };
	SDL_Rect quitButtonPos = { 412, 600, 200, 100 };

	bool enabled;

  public:
	MainMenu ();
	~MainMenu ();

	MainMenu (SDL_Renderer *renderer, TextureManager *textureManager,
	          FontManager *fontManager, Game *game);

	void Render () const;
	void HandleEvents (SDL_Event *event);
	void Enable ();
	bool IsEnabled () const;
};

#endif // USER_INTERFACE_MAIN_MENU_H_