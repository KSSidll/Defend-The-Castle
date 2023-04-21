#include "Enemy.h"
#include "PlayerSummon.h"

Enemy::Enemy () {}
Enemy::~Enemy () {}

void
Enemy::Move ()
{
	EntityObject::Move ();
}

Enemy::Enemy (SDL_Renderer *renderer, SDL_Texture *objTexture,
              const rapidjson::Value &object)
	: EntityObject (renderer, objTexture, object)
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
Enemy::DoDamage (int attack)
{
	EntityObject::DoDamage (attack);
	if (movementSpeed >= 6)
		movementSpeed = speedReference * health;
}

void
Enemy::HandleCollision (PlayerSummon *entity)
{
	Attack ();
	if (isAnimationDone && attacking)
		entity->DoDamage (attackDamage);
}
