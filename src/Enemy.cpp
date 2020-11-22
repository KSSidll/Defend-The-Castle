#include "Enemy.hpp"

void Enemy::Move()
{
    xShift += movementSpeed;
    destRect.x -= (int)xShift;
    xShift -= (int)xShift;
}

Enemy::Enemy(SDL_Texture* objTexture, rapidjson::Value& object, SDL_Renderer* renderer) : EntityObject(objTexture, object, renderer)
{

}

void Enemy::Update()
{
    if( isMoving ) Move();
}