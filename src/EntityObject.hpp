#pragma once
#include "MovableObject.hpp"

class EntityObject : public MovableObject
{
    protected:
        int health;
        int attackDamage;
        float movementSpeed;
        float attackInterval;
        float range;
        float timeSinceLastAttack = attackInterval / 2;
        
    public:
        EntityObject(){};
        ~EntityObject(){};
        EntityObject(rapidjson::Value& object, SDL_Renderer* renderer);

        void Update();
        float GetRange();
};