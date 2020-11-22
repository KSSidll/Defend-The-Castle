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
        PlayerSummon(SDL_Texture* objTexture, rapidjson::Value& object, SDL_Renderer* renderer);
        
        void Update();
        void EnemyCollision();
};