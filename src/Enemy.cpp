#include "Enemy.hpp"

void Enemy::Move()
{
    if( (movementSkipCount+1) * movementSpeed >= 1 )
    {
        destRect.x -= (movementSkipCount+1) * movementSpeed;
        movementSkipCount = 0;
    } else ++movementSkipCount;
}

Enemy::Enemy(rapidjson::Value& object, SDL_Renderer* renderer) : EntityObject(object, renderer)
{

}

void Enemy::Update()
{
    if( isMoving ) Move();
}