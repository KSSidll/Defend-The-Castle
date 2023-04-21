#ifndef USER_INTERFACE_USER_INTERFACE_H_
#define USER_INTERFACE_USER_INTERFACE_H_

#include "../Managers/FontManager.h"
#include "Menus/DifficultySelectionMenu.h"
#include "Menus/GameMenu.h"
#include "Menus/LoseMenu.h"
#include "Menus/MainMenu.h"
#include "Menus/PauseMenu.h"
#include "Menus/ShopMenu.h"
#include "Menus/WinMenu.h"
#include <SDL2/SDL.h>

class UserInterface
{
  private:
	const Game *game;
	FontManager *fontManager;
	GameMenu *gameMenu;
	PauseMenu *pauseMenu;
	MainMenu *mainMenu;
	DifficultySelectionMenu *difficultySelectionMenu;
	WinMenu *winMenu;
	LoseMenu *loseMenu;
	ShopMenu *shopMenu;

	bool bStatUpdate = false;

  public:
	UserInterface ();
	~UserInterface ();

	UserInterface (SDL_Renderer *renderer, TextureManager *textureManager,
	               Game *game, SummonDungeon *dungeon, Player *player,
	               rapidjson::Value *json);

	void Update ();
	void Render () const;
	void HandleEvents (SDL_Event *event);
	void Reset (float multiplier);
	void HardReset ();
	void Save (rapidjson::Document *saveJson) const;
	void Load (const rapidjson::Value *saveJson);
};

#endif // USER_INTERFACE_USER_INTERFACE_H_
