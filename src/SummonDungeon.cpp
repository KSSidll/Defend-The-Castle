#include "SummonDungeon.hpp"

void SummonDungeon::Update()
{
    for(auto summon : this->objectArray)
    {
        summon->Update();
    }
}

void SummonDungeon::Render()
{
    for(auto summon : this->objectArray)
    {
        summon->Render();
    }
}

void SummonDungeon::SummonObject(rapidjson::Value& object, SDL_Renderer* renderer)
{
    PlayerSummon *summon = new PlayerSummon(object, renderer);
    this->objectArray.push_back(summon);
}