#ifndef USER_INTERFACE_DIFFICULTY_SELECTION_MENU_H_
#define USER_INTERFACE_DIFFICULTY_SELECTION_MENU_H_

#include "../../Game.h"
#include "../../Managers/FontManager.h"
#include "../../Objects/SceneObject.h"
#include "../Components/LabeledButton.h"
#include <deque>

class DifficultySelectionMenu
{
  private:
	std::deque<LabeledButton> buttons;
	SceneObject background;
	UILabel label;

	float easy;
	float medium;
	float hard;

	SDL_Rect easyButtonPos = { 412, 200, 200, 100 };
	SDL_Rect mediumButtonPos = { 412, 400, 200, 100 };
	SDL_Rect hardButtonPos = { 412, 600, 200, 100 };

  public:
	DifficultySelectionMenu ();
	~DifficultySelectionMenu ();

	DifficultySelectionMenu (SDL_Renderer *renderer,
	                         TextureManager *textureManager,
	                         FontManager *fontManager, Game *game,
	                         const rapidjson::Value *json);

	void Render () const;
	void HandleEvents (SDL_Event *event);
};

#endif // USER_INTERFACE_DIFFICULTY_SELECTION_MENU_H_