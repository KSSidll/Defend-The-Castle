#pragma once
#include "EntityObject.hpp"

class Enemy : virtual public EntityObject 
{
    public:
        Enemy(){};
        ~Enemy(){};
        Enemy(rapidjson::Value& object, SDL_Renderer* renderer);
};