#ifndef MANAGERS_SUMMON_DUNGEON_H_
#define MANAGERS_SUMMON_DUNGEON_H_

#include <SDL2/SDL.h>
#include <deque>
#include <rapidjson/fwd.h>

class TextureManager;
class Player;
class PlayerSummon;

class SummonDungeon
{
  private:
	TextureManager *textureManager;
	SDL_Renderer *renderer;
	Player *player;

	std::deque<PlayerSummon> *objectArray;
	std::deque<PlayerSummon *> pendingKills;

	int id = 0;

	void KillPending ();
	void KillSummonObject (PlayerSummon *summon);

  public:
	SummonDungeon ();
	~SummonDungeon ();

	SummonDungeon (TextureManager *textureManager, SDL_Renderer *renderer,
	               Player *player);

	void Update ();
	void Render ();
	void Reset ();
	void SummonObject (rapidjson::Value &object);

	std::deque<PlayerSummon> *getObjectArray ();
};

#endif // MANAGERS_SUMMON_DUNGEON_H_