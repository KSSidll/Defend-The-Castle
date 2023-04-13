#include "Enemy.h"
#include "PlayerSummon.h"
#include <rapidjson/document.h>

void
Enemy::Move ()
{
	EntityObject::Move ();
}

Enemy::Enemy (SDL_Texture *objTexture, rapidjson::Value &object,
              SDL_Renderer *renderer)
	: EntityObject (objTexture, object, renderer)
{
	movementVector = -1;
	speedReference = (float)movementSpeed / (float)health;
}

void
Enemy::Update ()
{
	EntityObject::Update ();
	if (isMoving)
		Move ();
	if (isAnimationDone && !alive)
		pendingKill = true;
}

void
Enemy::Render ()
{
	EntityObject::Render ();
}

void
Enemy::DoDamage (int attack)
{
	EntityObject::DoDamage (attack);
	if (movementSpeed >= 6)
		movementSpeed = speedReference * health;
}

void
Enemy::HandleCollision ()
{
	EntityObject::HandleCollision ();
}

void
Enemy::HandleCollision (PlayerSummon *entity)
{
	Attack ();
	if (isAnimationDone && attacking)
		entity->DoDamage (attackDamage);
}
