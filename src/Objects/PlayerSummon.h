#ifndef OBJECTS_PLAYER_SUMMON_H_
#define OBJECTS_PLAYER_SUMMON_H_

#include "EntityObject.h"

// Recurrent dependency
class Enemy;

class PlayerSummon : virtual public EntityObject
{
  private:
	int cost;

  public:
	PlayerSummon (){};
	~PlayerSummon (){};

	PlayerSummon (SDL_Texture *objTexture, const rapidjson::Value &object,
	              SDL_Renderer *renderer);
	PlayerSummon (SDL_Texture *objTexture, const rapidjson::Value &object,
	              SDL_Renderer *renderer, int id);

	void Update ();
	void Render () const;
	void HandleCollision ();
	void HandleCollision (Enemy *entity);
};

#endif // OBJECTS_PLAYER_SUMMON_H_