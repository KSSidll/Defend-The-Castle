#include "PlayerSummon.h"
#include "Enemy.h"

PlayerSummon::PlayerSummon () {}
PlayerSummon::~PlayerSummon () {}

PlayerSummon::PlayerSummon (SDL_Renderer *renderer, SDL_Texture *objTexture,
                            const rapidjson::Value &object)
	: EntityObject (renderer, objTexture, object)
{
	cost = object["cost"].GetInt ();
}

PlayerSummon::PlayerSummon (SDL_Renderer *renderer, SDL_Texture *objTexture,
                            const rapidjson::Value &object, uint64_t id)
	: PlayerSummon::PlayerSummon (renderer, objTexture, object)
{
	this->id = id;
}

void
PlayerSummon::Update ()
{
	EntityObject::Update ();

	if (isMoving)
		Move ();
	if (isAnimationDone && animationYpos == animationLengths.size () - 1)
		pendingKill = true;
}

void
PlayerSummon::HandleCollision (Enemy *entity)
{
	Attack ();
	if (isAnimationDone && attacking)
		entity->DoDamage (attackDamage);
}