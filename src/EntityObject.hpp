#pragma once
#include "MovableObject.hpp"

class EntityObject : public MovableObject
{
    protected:
        bool pendingKill = false;
        bool alive = true;
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

        void Kill();
        void Render();
        float GetRange();
        int GetId(){ return id; };
        bool KillPending(){ return pendingKill; };
        bool Alive(){ return alive; };
};