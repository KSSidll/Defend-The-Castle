#pragma once
#include "EntityObject.hpp"

class PlayerSummon : virtual public EntityObject
{
    private:
        int cost;

        void Move();

    public:
        PlayerSummon(){};
        ~PlayerSummon(){};
        PlayerSummon(rapidjson::Value& object, SDL_Renderer* renderer);
        
        void Update(); 
};