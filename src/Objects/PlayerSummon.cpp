#include "PlayerSummon.h"
#include "Enemy.h"
#include <rapidjson/document.h>

PlayerSummon::PlayerSummon (SDL_Texture *objTexture, rapidjson::Value &object,
                            SDL_Renderer *renderer)
	: EntityObject (objTexture, object, renderer)
{
	cost = object["cost"].GetInt ();
}

PlayerSummon::PlayerSummon (SDL_Texture *objTexture, rapidjson::Value &object,
                            SDL_Renderer *renderer, int id)
	: PlayerSummon::PlayerSummon (objTexture, object, renderer)
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
PlayerSummon::Render ()
{
	EntityObject::Render ();
}

void
PlayerSummon::HandleCollision ()
{
	EntityObject::HandleCollision ();
}

void
PlayerSummon::HandleCollision (Enemy *entity)
{
	Attack ();
	if (isAnimationDone && attacking)
		entity->DoDamage (attackDamage);
}