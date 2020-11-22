#include "EntityObject.hpp"

EntityObject::EntityObject(SDL_Texture* objTexture, rapidjson::Value& object, SDL_Renderer* renderer) : MovableObject(objTexture, object, renderer)
{
    health = object["health"].GetInt();
    attackDamage = object["attackDamage"].GetInt();
    movementSpeed = object["movementSpeed"].GetFloat();
    attackInterval = object["attackInterval"].GetFloat();
    range = object["range"].GetFloat();
}

void EntityObject::Update()
{
    
}

float EntityObject::GetRange()
{
    return range;
}