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
    GameObject *objeect = new GameObject(object, renderer);
    this->objectArray.push_back(objeect);
}

