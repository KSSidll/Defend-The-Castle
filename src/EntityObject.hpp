#pragma once
#include "MovableObject.hpp"

class EntityObject : public MovableObject
{
    protected:
        int id;
        int health;
        int attackDamage;
        int range;
        float movementSpeed;
        float attackInterval;
        float timeSinceLastAttack = attackInterval / 2;
        
    public:
        EntityObject(){};
        ~EntityObject(){};
        EntityObject(SDL_Texture* objTexture, rapidjson::Value& object, SDL_Renderer* renderer);

        float GetRange();
        int GetId(){ return id; };

};