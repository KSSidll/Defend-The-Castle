#include "ObjectDungeon.hpp"

ObjectDungeon::ObjectDungeon()
{

}

void ObjectDungeon::summonObject(rapidjson::Value& object, SDL_Renderer* renderer)
{
    GameObject tmpObject(object, renderer);
    this->objectArray.push_back(tmpObject);
}

