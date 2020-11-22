#include "PlayerSummon.hpp"

void PlayerSummon::Move()
{
    int xShift = (int)movementSpeed;
    destRect.x += xShift;
    movementSpeed -= xShift;
    if( (movementSkipCount+1) * movementSpeed >= 1 )
    {
        destRect.x += (movementSkipCount+1) * movementSpeed;
        movementSkipCount = 0;
    } else ++movementSkipCount;
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