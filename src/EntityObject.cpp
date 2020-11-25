#include "EntityObject.hpp"

thenvoid EntityObject::Move()
{
    xShift += movementSpeed;
    MovableObject::Move();
}

EntityObject::EntityObject(SDL_Texture* objTexture, rapidjson::Value& object, SDL_Renderer* renderer) : MovableObject(objTexture, object, renderer)
{
    health = object["health"].GetInt();
    attackDamage = object["attackDamage"].GetInt();
    range = object["range"].GetInt();
    attackSpeed = object["attackSpeed"].GetInt();
    movementSpeed = object["movementSpeed"].GetFloat();
    animationSpeed *= movementSpeed * 10;
}

void EntityObject::Kill()
{
    alive = false;
    isMoving = false;
    animationYpos = animationLengths.size()-1;
    animationSpeed = 20;
    animationXpos = 0;
    animationFramesSkipped = 0;
}

void EntityObject::Attack()
{
    attacking = true;
    isMoving = false;
    animationYpos = 1;
    animationSpeed = attackSpeed;
    animationXpos = 0;
    animationFramesSkipped = 0;
}

void EntityObject::Update()
{
    MovableObject::Update();
}

void EntityObject::Render()
{
    if( !pendingKill )
    {
        MovableObject::Render();
    }
}