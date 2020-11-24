#include "SummonDungeon.hpp"
#include <iostream>
#include <numeric>
#include <string_view>

void SummonDungeon::Update()
{
    for(auto summon : objectArray)
    {
        summon->Update();
    }
}

void SummonDungeon::Render()
{
    for(auto summon : objectArray)
    {
        summon->Render();
    }
}

void SummonDungeon::SummonObject(SDL_Texture* objTexture, rapidjson::Value& object, SDL_Renderer* renderer)
{
    PlayerSummon *summon = new PlayerSummon(objTexture, object, renderer, id);
    objectArray.push_back(summon);
    ++id;
}

void SummonDungeon::KillSummonObject(int id)
{
    objectArray.erase(objectArray.begin() + id - idOffset);
    ++idOffset;
}