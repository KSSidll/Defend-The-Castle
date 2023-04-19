#ifndef USER_INTERFACE_GAME_MENU_H_
#define USER_INTERFACE_GAME_MENU_H_

#include "../../Game.h"
#include "../../Managers/FontManager.h"
#include "../../Objects/SceneObject.h"
#include "../Components/LabeledButton.h"
#include <deque>

struct EntityButton
{
	LabeledButton button;
	const char *entity_type;
};

class GameMenu
{
  private:
	const rapidjson::Value *json;
	const Player *player;
	const Game *game;

	std::deque<EntityButton> buttons;

	SDL_Rect gameInfoBackgroundPos = { 0, 0, 1024, 100 };
	SceneObject gameInfoBackground;

	UILabel levelInfo;
	UILabel playerFujika;
	UILabel playerFuko;

	SceneObject enemyStatsBackground;
	UILabel enemyNameLabel;
	UILabel enemyStatsLabel;

	void UpdateEnemyStatsLabel (float multiplier = 1);
	void UpdateEntitiesStatsLabel ();

  public:
	GameMenu ();
	~GameMenu ();

	GameMenu (const rapidjson::Value *json, SummonDungeon *dungeon,
	          SDL_Renderer *renderer, TextureManager *textureManager,
	          const Player *player, const Game *game,
	          FontManager *fontManager);

	void Render () const;
	void HandleEvents (SDL_Event *event);
	void Reset (float multiplier);
	void Update (bool bStatUpdate = false);
};

#endif // USER_INTERFACE_GAME_MENU_H_
