#ifndef USER_INTERFACE_PAUSE_MENU_H_
#define USER_INTERFACE_PAUSE_MENU_H_

#include "../../Game.h"
#include "../../Managers/FontManager.h"
#include "../../Objects/SceneObject.h"
#include "../Components/LabeledButton.h"
#include <deque>

class PauseMenu
{
  private:
	std::deque<LabeledButton> buttons;
	SceneObject background;
	UILabel label;

	SDL_Rect resumeButtonPos = { 412, 200, 200, 100 };
	SDL_Rect exitButtonPos = { 412, 400, 200, 100 };

  public:
	PauseMenu ();
	~PauseMenu ();

	PauseMenu (SDL_Renderer *renderer, TextureManager *textureManager,
	           FontManager *fontManager, Game *game);

	void Render () const;
	void HandleEvents (SDL_Event *event);
};

#endif // USER_INTERFACE_PAUSE_MENU_H_