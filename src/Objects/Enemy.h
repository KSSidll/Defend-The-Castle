#ifndef OBJECTS_ENEMY_H_
#define OBJECTS_ENEMY_H_

#include "EntityObject.h"

// Recurrent dependency
class PlayerSummon;

class Enemy : public EntityObject
{
  private:
	float speedReference;

	void Move ();

  public:
	Enemy (){};
	~Enemy (){};

	Enemy (SDL_Texture *objTexture, const rapidjson::Value &object,
	       SDL_Renderer *renderer);

	void Update ();
	void DoDamage (int attack);
	void HandleCollision (PlayerSummon *entity);
};

#endif // OBJECTS_ENEMY_H_