#pragma once
#include "MovableObject.hpp"

class EntityObject : public MovableObject
{
    protected:
        int id;
        int health;
        int attackDamage;
        float movementSpeed;
        float attackInterval;
        float range;
        float timeSinceLastAttack = attackInterval / 2;
        
    public:
        EntityObject(){};
        ~EntityObject(){};
        EntityObject(SDL_Texture* objTexture, rapidjson::Value& object, SDL_Renderer* renderer);

        void Update();
        int GetId(){ return id; };
        float GetRange();
};