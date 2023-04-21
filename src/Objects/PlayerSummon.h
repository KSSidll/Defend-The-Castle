#ifndef OBJECTS_PLAYER_SUMMON_H_
#define OBJECTS_PLAYER_SUMMON_H_

#include "EntityObject.h"

// Recurrent dependency
class Enemy;

class PlayerSummon : public EntityObject
{
  private:
	int cost;

  public:
	PlayerSummon ();
	~PlayerSummon ();

	PlayerSummon (SDL_Renderer *renderer, SDL_Texture *objTexture,
	              const rapidjson::Value &object);
	PlayerSummon (SDL_Renderer *renderer, SDL_Texture *objTexture,
	              const rapidjson::Value &object, uint64_t id);

	void Update ();
	void HandleCollision (Enemy *entity);
};

#endif // OBJECTS_PLAYER_SUMMON_H_