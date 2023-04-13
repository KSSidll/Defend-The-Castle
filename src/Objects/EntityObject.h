#ifndef OBJECTS_ENTITY_OBJECT_H_
#define OBJECTS_ENTITY_OBJECT_H_

#include "MovableObject.h"
#include <rapidjson/fwd.h>

class EntityObject : public MovableObject
{
  protected:
	bool attacking = false;
	bool pendingKill = false;
	bool alive = true;
	int id;
	int health;
	int attackDamage;
	int range;
	int movementSpeed;
	int attackSpeed;

	void Move ();

  public:
	EntityObject (){};
	~EntityObject (){};

	EntityObject (SDL_Texture *objTexture, rapidjson::Value &object,
	              SDL_Renderer *renderer);

	void Kill ();
	void Attack ();
	void SetObjectValues (rapidjson::Value &object, float multiplier);
	void SetObjectValues (rapidjson::Value &object);
	void Update ();
	void Render ();
	void Reset ();
	void Reset (float multipier);
	void HandleCollision ();
	void DoDamage (int damage);

	float GetRange ();
	int GetId ();
	int GetHealth ();
	bool KillPending ();
	bool Alive ();
};

#endif // OBJECTS_ENTITY_OBJECT_H_