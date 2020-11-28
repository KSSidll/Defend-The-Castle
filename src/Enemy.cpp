#include "Enemy.hpp"

void Enemy::Move()
{
    movementVector = -1;
    EntityObject::Move();
}

Enemy::Enemy(SDL_Texture* objTexture, rapidjson::Value& object, SDL_Renderer* renderer) : EntityObject(objTexture, object, renderer)
{

}

void Enemy::Update()
{
    EntityObject::Update();
    if( isMoving ) Move();
    if( isAnimationDone && !alive ) pendingKill = true;
}

void Enemy::Render()
{
    EntityObject::Render();
}

void Enemy::HandleCollision()
{
    EntityObject::HandleCollision();
}

void Enemy::HandleCollision(PlayerSummon* entity)
{
    Attack();
    if( isAnimationDone && attacking )
        entity->DoDamage( attackDamage );
}
