#pragma once
#include "EntityObject.hpp"

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
};