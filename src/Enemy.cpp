#include "Enemy.hpp"

void Enemy::Move()
{
    int xShift = (int)movementSpeed;
    destRect.x += xShift;
    movementSpeed -= xShift;
    if( (movementSkipCount+1) * movementSpeed >= 1 )
    {
        destRect.x -= (movementSkipCount+1) * movementSpeed;
        movementSkipCount = 0;
    } else ++movementSkipCount;
}

Enemy::Enemy(SDL_Texture* objTexture, rapidjson::Value& object, SDL_Renderer* renderer) : EntityObject(objTexture, object, renderer)
{

}

void Enemy::Update()
{
    if( isMoving ) Move();
}