#ifndef ENGINE_GAME_H_
#define ENGINE_GAME_H_

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <rapidjson/fwd.h>

class SummonDungeon;
class TextureManager;
class UserInterface;
class Player;
class Enemy;
class SceneObject;

class Game
{
  private:
	SDL_Window *window;
	SDL_Renderer *renderer;
	rapidjson::Document *objectsDoc;
	rapidjson::Document *saveDoc;
	SummonDungeon *summonDungeon;
	TextureManager *textureManager;
	UserInterface *userInterface;
	Player *player;
	Enemy *enemy;
	SceneObject *background;

	float enemyStatsLevelMultiplier = 1.1;
	int level = 0;

	bool menuFlag = true;
	bool isPaused = true;
	bool mainMenu = true;
	bool difficultyMenu = false;
	bool winMenu = false;
	bool loseMenu = false;
	bool shopMenu = false;
	bool isRunning;

	void ResetMenus ();

  public:
	Game ();
	~Game ();

	void Init (const char *title, int width, int height, bool fullscreen);

	void HandleEvents ();
	void Update ();
	void Render ();
	void Clean ();
	void HandleCollisions ();
	void HardReset ();
	void Reset ();
	void Save (bool incrementLevel = false);
	void Load ();

	void Pause ();
	void UnPause ();
	void Quit ();
	void IncreaseLevel ();
	void ChangeEnemyLevelMultiplier (float multiplier);

	bool Running ();
	bool Paused ();
	int Level ();

	void LoseGame ();
	void NewGame ();
	void Start ();
	void MainMenu ();
	void WinMenu ();
	void ShopMenu ();

	bool isMainMenu ();
	bool isDifficultyMenu ();
	bool isWinMenu ();
	bool isLoseMenu ();
	bool isShopMenu ();
};

#endif // ENGINE_GAME_H_