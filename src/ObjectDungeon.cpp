#include "ObjectDungeon.hpp"

ObjectDungeon::ObjectDungeon()
{

}

void ObjectDungeon::summonObject(rapidjson::Value& object, SDL_Renderer* renderer)
{
    this->objectArray.push_back(new GameObject(object, renderer));
}

