#pragma once
#include "EntityObject.h"

class Enemy;

class PlayerSummon : virtual public EntityObject
{
    private:
        int cost;

    public:
        PlayerSummon(){};
        ~PlayerSummon(){};

        PlayerSummon( SDL_Texture* objTexture, rapidjson::Value& object, SDL_Renderer* renderer );
        PlayerSummon( SDL_Texture* objTexture, rapidjson::Value& object, SDL_Renderer* renderer, int id );

        void Update();
        void Render();
        void JsonReset();
        void HandleCollision();
        void HandleCollision( Enemy* entity );
};