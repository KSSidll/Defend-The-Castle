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

std::deque<int> SummonDungeon::GetPositions()
{
    std::deque<int> positionsArray;

    for(auto summon : objectArray)
    {
        positionsArray.push_back(summon->GetPosition());
    }

    return positionsArray;
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