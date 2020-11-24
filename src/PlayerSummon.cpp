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

PlayerSummon::PlayerSummon(SDL_Texture* objTexture, rapidjson::Value& object, SDL_Renderer* renderer, int id) : EntityObject(objTexture, object, renderer)
{
    cost = object["cost"].GetInt();
    this->id = id;
}

void PlayerSummon::Update()
{
    if( isMoving ) Move();

    //chec
    if( isAnimationDone && animationYpos == animationLengths.size()-1 ) pendingKill = true;
}

void PlayerSummon::EnemyCollision()
{
    isMoving = false;
}