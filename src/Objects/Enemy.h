#ifndef OBJECTS_ENEMY_H_
#define OBJECTS_ENEMY_H_

#include "EntityObject.h"
#include <rapidjson/fwd.h>

class PlayerSummon;

class Enemy : virtual public EntityObject
{
    private:
        float speedReference;

        void Move();

    public:
        Enemy(){};
        ~Enemy(){};

        Enemy( SDL_Texture* objTexture, rapidjson::Value& object, SDL_Renderer* renderer );

        void Update();
        void Render();
        void DoDamage( int attack );
        void HandleCollision();
        void HandleCollision( PlayerSummon* entity );
};

#endif // OBJECTS_ENEMY_H_