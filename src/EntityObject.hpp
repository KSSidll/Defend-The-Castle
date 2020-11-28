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
        int movementSpeed;
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
        void HandleCollision();
        void DoDamage(int damage){ health -= damage; };

        float GetRange(){ return range; };
        int GetId(){ return id; };
        int GetHealth(){ return health; };
        bool KillPending(){ return pendingKill; };
        bool Alive(){ return alive; };
};