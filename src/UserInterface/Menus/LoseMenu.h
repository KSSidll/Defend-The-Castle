#ifndef USER_INTERFACE_LOSE_MENU_H_
#define USER_INTERFACE_LOSE_MENU_H_

#include "../../Game.h"
#include "../../Managers/FontManager.h"
#include "../../Objects/SceneObject.h"
#include "../Components/LabeledButton.h"
#include <deque>

// Recurrent dependency
class UserInterface;

class LoseMenu
{
  private:
	std::deque<LabeledButton> buttons;
	SceneObject background;
	UILabel label;

	SDL_Rect exitButtonPos = { 362, 300, 300, 150 };
	SDL_Rect loadButtonPos = { 362, 600, 300, 100 };

	bool enabled;

  public:
	LoseMenu ();
	~LoseMenu ();

	LoseMenu (SDL_Renderer *renderer, TextureManager *textureManager,
	          FontManager *fontManager, Game *game,
	          UserInterface *userInterface);

	void Render () const;
	void HandleEvents (SDL_Event *event);
	void Enable ();
	bool IsEnabled () const;
};

#endif // USER_INTERFACE_LOSE_MENU_H_