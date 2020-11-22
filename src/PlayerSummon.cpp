#include "PlayerSummon.hpp"

void PlayerSummon::Move()
{
    xShift += movementSpeed;
    destRect.x += (int)xShift;
    xShift -= (int)xShift;
}

PlayerSummon::PlayerSummon(SDL_Texture* objTexture, rapidjson::Value& object, SDL_Renderer* renderer) : EntityObject(objTexture, object, renderer)
{
    cost = object["cost"].GetInt();
}

void PlayerSummon::Update()
{
    if( isMoving ) Move();
}

void PlayerSummon::EnemyCollision()
{
    isMoving = false;
}