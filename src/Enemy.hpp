#pragma once
#include "EntityObject.hpp"

class Enemy : virtual public EntityObject 
{
    private:
        void Move();

    public:
        Enemy(){};
        ~Enemy(){};
        Enemy(rapidjson::Value& object, SDL_Renderer* renderer);

        void Update();
        std::pair<int,int> GetPosition();
};