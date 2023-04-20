#ifndef OBJECTS_ENTITY_OBJECT_H_
#define OBJECTS_ENTITY_OBJECT_H_

#include "MovableObject.h"

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

  public:
	EntityObject (){};
	~EntityObject (){};

	EntityObject (SDL_Texture *objTexture, const rapidjson::Value &object,
	              SDL_Renderer *renderer);

	void Move ();
	void Kill ();
	void Attack ();
	void SetObjectValues (const rapidjson::Value &object, float multiplier);
	void SetObjectValues (const rapidjson::Value &object);
	void Update ();
	void Render () const;
	void Reset ();
	void Reset (float multipier);
	void HandleCollision ();
	void DoDamage (int damage);

	float GetRange () const;
	int GetId () const;
	int GetHealth () const;
	bool KillPending () const;
	bool Alive () const;
};

#endif // OBJECTS_ENTITY_OBJECT_H_