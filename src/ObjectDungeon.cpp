#include "ObjectDungeon.hpp"

ObjectDungeon::ObjectDungeon()
{

}

ObjectDungeon::~ObjectDungeon()
{

}

void ObjectDungeon::Update()
{
    for(auto object : this->objectArray)
    {
        object->Update();
    }
    
}

void ObjectDungeon::Render()
{
    for(auto object : this->objectArray)
    {
        object->Render();
    }
    
}

void ObjectDungeon::SummonObject(rapidjson::Value& object, SDL_Renderer* renderer)
{
    PlayerSummon *summon = new PlayerSummon(object, renderer);
    this->objectArray.push_back(summon);
}