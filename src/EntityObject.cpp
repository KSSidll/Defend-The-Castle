#include "EntityObject.hpp"

EntityObject::EntityObject(SDL_Texture* objTexture, rapidjson::Value& object, SDL_Renderer* renderer) : MovableObject(objTexture, object, renderer)
{
    health = object["health"].GetInt();
    attackDamage = object["attackDamage"].GetInt();
    range = object["range"].GetInt();
    movementSpeed = object["movementSpeed"].GetFloat();
    attackInterval = object["attackInterval"].GetFloat();
}

float EntityObject::GetRange()
{
    return range;
}

void EntityObject::Kill()
{
    alive = false;
    animationYpos = animationLengths.size()-1;
    animationXpos = 0;
    animationFramesSkipped = 0;
}