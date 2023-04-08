#include "EntityObject.h"
#include <rapidjson/document.h>

void EntityObject::Move()
{
    xShift += (float)(movementSpeed)/20;
    MovableObject::Move();
}

EntityObject::EntityObject( SDL_Texture* objTexture, rapidjson::Value& object, SDL_Renderer* renderer) : MovableObject(objTexture, object, renderer )
{
    SetObjectValues( object );
}

void EntityObject::Kill()
{
    if( alive )
    {
        alive = false;
        attacking = false;
        isMoving = false;
        animationYpos = animationLengths.size()-1;
        animationSpeed = 20;
        animationXpos = 0;
        animationFramesSkipped = 0;
    }
}

void EntityObject::Attack()
{
    if( alive && !attacking )
    {
        attacking = true;
        isMoving = false;
        animationYpos = 1;
        animationSpeed = attackSpeed;
        animationXpos = 0;
        animationFramesSkipped = 0;
    }
}

void EntityObject::SetObjectValues( rapidjson::Value& object )
{
    health = object["health"].GetInt();
    attackDamage = object["attackDamage"].GetInt();
    range = object["range"].GetInt();
    attackSpeed = object["attackSpeed"].GetInt();
    movementSpeed = object["movementSpeed"].GetInt();
    animationSpeed = movementSpeed;
}

void EntityObject::SetObjectValues( rapidjson::Value& object, float multiplier )
{
    health = object["health"].GetInt() * multiplier;
    attackDamage = object["attackDamage"].GetInt() * multiplier;
    range = object["range"].GetInt();
    attackSpeed = object["attackSpeed"].GetInt() * multiplier;
    movementSpeed = object["movementSpeed"].GetInt() * multiplier;
    animationSpeed = movementSpeed;
}

void EntityObject::Update()
{
    if( health <= 0 && alive ) Kill();

    if( attacking && isAnimationDone )
    {
        attacking = false;
        isMoving = true;
        animationYpos = 0;
        animationSpeed = movementSpeed;
        srcRect.x = OsrcRect.x;
        srcRect.y = OsrcRect.y;
    }

    MovableObject::Update();
}

void EntityObject::Render()
{
    if( !pendingKill )
    {
        MovableObject::Render();
    }
}

void EntityObject::Reset()
{
    attacking = false;
    pendingKill = false;
    alive = true;

    MovableObject::Reset();
    SetObjectValues( *originalJsonValues );
}

void EntityObject::Reset( float multiplier )
{
    attacking = false;
    pendingKill = false;
    alive = true;

    MovableObject::Reset();
    SetObjectValues( *originalJsonValues, multiplier );
}

void EntityObject::HandleCollision()
{
    if( !attacking )
    {
        isMoving = false;
        animationYpos = 0;
        animationSpeed = 0;
        srcRect.x = OsrcRect.x;
        srcRect.y = OsrcRect.y;
    }
}