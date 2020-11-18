#include "ObjectDungeon.hpp"

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
    this->objectArray.push_back(new GameObject(object, renderer));
}

