#ifndef USER_INTERFACE_GAME_MENU_H_
#define USER_INTERFACE_GAME_MENU_H_

#include "../Components/Button.h"
#include <SDL2/SDL.h>
#include <deque>
#include <rapidjson/fwd.h>

struct LabeledButton;

class Button;
class Game;
class SummonDungeon;
class Player;
class TextureManager;
class UILabel;
class SceneObject;

class GameMenu
{
  private:
	rapidjson::Value *json;
	SDL_Renderer *renderer;
	SummonDungeon *dungeon;
	Player *player;
	Game *game;

	std::deque<LabeledButton> buttons;

	SDL_Rect gameInfoBackgroundPos = { 0, 0, 1024, 100 };
	SceneObject *gameInfoBackground;

	UILabel *levelInfo;
	UILabel *playerFujika;
	UILabel *playerFuko;

	SceneObject *enemyStatsBackground;
	UILabel *enemyNameLabel;
	UILabel *enemyStatsLabel;

	void UpdateEnemyStatsLabel (float multiplier = 1);
	void UpdateEntitiesStatsLabel ();

  public:
	GameMenu ();
	~GameMenu ();

	GameMenu (rapidjson::Value *json, SummonDungeon *dungeon,
	          SDL_Renderer *renderer, TextureManager *textureManager,
	          Player *player, Game *game);

	void Render ();
	void HandleEvents (SDL_Event *event);
	void Reset (float multiplier);
	void Update (bool bStatUpdate = false);
};

#endif // USER_INTERFACE_GAME_MENU_H_
