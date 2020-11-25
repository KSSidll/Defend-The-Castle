#pragma once
#include "EntityObject.hpp"
#include "PlayerSummon.hpp"

class PlayerSummon;

class Enemy : virtual public EntityObject 
{
    private:
        void Move();

    public:
        Enemy(){};
        ~Enemy(){};
        Enemy(SDL_Texture* objTexture, rapidjson::Value& object, SDL_Renderer* renderer);

        void Update();
        void Render();
        void EnemyCollision();
        void EnemyCollision(PlayerSummon* entity);
};