#include "EntityObject.hpp"

EntityObject::EntityObject(rapidjson::Value& object, SDL_Renderer* renderer) : MovableObject(object, renderer)
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