#ifndef MANAGERS_SUMMON_DUNGEON_H_
#define MANAGERS_SUMMON_DUNGEON_H_

#include "../Objects/PlayerSummon.h"
#include "Player.h"
#include "TextureManager.h"
#include <deque>
#include <stdint.h>

class SummonDungeon
{
  private:
	const TextureManager *textureManager;
	SDL_Renderer *renderer;
	Player *player;

	std::deque<PlayerSummon> objectArray;
	std::deque<PlayerSummon *> pendingKills;

	uint64_t id = 0;

	void KillPending ();
	void KillSummonObject (PlayerSummon *summon);

  public:
	SummonDungeon ();
	~SummonDungeon ();

	SummonDungeon (const TextureManager *textureManager,
	               SDL_Renderer *renderer, Player *player);

	void Update ();
	void Render () const;
	void Reset ();
	void SummonObject (const rapidjson::Value &object);

	const std::deque<PlayerSummon> *getObjectArray () const;
};

#endif // MANAGERS_SUMMON_DUNGEON_H_