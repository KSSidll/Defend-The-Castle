#ifndef OBJECTS_ENTITY_OBJECT_H_
#define OBJECTS_ENTITY_OBJECT_H_

#include "MovableObject.h"
#include <rapidjson/fwd.h>

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

        EntityObject( SDL_Texture* objTexture, rapidjson::Value& object, SDL_Renderer* renderer );

        void Kill();
        void Attack();
        void SetObjectValues( rapidjson::Value& object );
        void SetObjectValues( rapidjson::Value& object, float multiplier );
        void Update();
        void Render();
        void Reset();
        void Reset( float multipier );
        void HandleCollision();
        void DoDamage( int damage ){ health -= damage; };

        float GetRange(){ return range; };
        int GetId(){ return id; };
        int GetHealth(){ return health; };
        bool KillPending(){ return pendingKill; };
        bool Alive(){ return alive; };
};

#endif // OBJECTS_ENTITY_OBJECT_H_