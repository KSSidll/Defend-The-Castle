#pragma once
#include "MovableObject.hpp"

class EntityObject : public MovableObject
{
    protected:
        bool attacking = false;
        bool pendingKill = false;
        bool alive = true;
        int id;
        int health;
        int attackDamage;
        int range;
        float movementSpeed;
        int attackSpeed;

        void Move();
        
    public:
        EntityObject(){};
        ~EntityObject(){};
        EntityObject(SDL_Texture* objTexture, rapidjson::Value& object, SDL_Renderer* renderer);

        void Kill();
        void Attack();
        void Update();
        void Render();

        float GetRange(){ return range; };
        int GetId(){ return id; };
        bool KillPending(){ return pendingKill; };
        bool Alive(){ return alive; };
};