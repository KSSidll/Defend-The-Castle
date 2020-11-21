#pragma once
#include "EntityObject.hpp"

class PlayerSummon : public EntityObject
{
    private:
        int cost;
        void Move();

    public:
        PlayerSummon(){};
        ~PlayerSummon(){};
        PlayerSummon(rapidjson::Value& object, SDL_Renderer* renderer);
        PlayerSummon(rapidjson::Value& object, SDL_Renderer* renderer, int id);
        
        void Update();
        void EnemyCollision();
};