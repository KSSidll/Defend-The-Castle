#include "PlayerSummon.hpp"

void PlayerSummon::Move()
{
    if( (movementSkipCount+1) * movementSpeed >= 1 )
    {
        destRect.x += (movementSkipCount+1) * movementSpeed;
        movementSkipCount = 0;
    } else ++movementSkipCount;
}

PlayerSummon::PlayerSummon(rapidjson::Value& object, SDL_Renderer* renderer) : EntityObject(object, renderer)
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