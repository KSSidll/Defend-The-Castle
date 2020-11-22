#include "PlayerSummon.hpp"

PlayerSummon::PlayerSummon(rapidjson::Value& object, SDL_Renderer* renderer) : EntityObject(object, renderer)
{
    cost = object["cost"].GetInt();
}