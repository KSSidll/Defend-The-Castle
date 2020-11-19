#include "SummonDungeon.hpp"

void SummonDungeon::Update()
{
    for(auto object : this->objectArray)
    {
        object->Update();
    }
    
}

void SummonDungeon::Render()
{
    for(auto object : this->objectArray)
    {
        object->Render();
    }
    
}

void SummonDungeon::SummonObject(rapidjson::Value& object, SDL_Renderer* renderer)
{
    PlayerSummon *summon = new PlayerSummon(object, renderer);
    this->objectArray.push_back(summon);
}