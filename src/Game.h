#ifndef ENGINE_GAME_H_
#define ENGINE_GAME_H_

#define SDL_MAIN_HANDLED
#include "Objects/SceneObject.h"
#include <SDL2/SDL.h>
#include <rapidjson/document.h>

class SummonDungeon;
class TextureManager;
class UserInterface;
class Player;
class Enemy;

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
	SceneObject background;

	float enemyStatsLevelMultiplier = 1.1;
	int level = 0;

	bool isPaused;
	bool isRunning;

  public:
	Game ();
	~Game ();

	void Init (const char *title, int width, int height, bool fullscreen);

	void HandleEvents ();
	void Update ();
	void Render ();
	void HandleCollisions ();
	void HardReset ();
	void Reset ();
	void Save (bool incrementLevel = false);
	void Load ();

	void Pause ();
	void UnPause ();
	void LoseGame ();
	void WinGame ();
	void NewGame ();
	void Quit ();
	void IncreaseLevel ();
	void ChangeEnemyLevelMultiplier (float multiplier);

	int GetLevel () const;
	bool IsRunning () const;
	bool IsPaused () const;
};

#endif // ENGINE_GAME_H_