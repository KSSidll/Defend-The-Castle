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

std::deque< std::pair<int,int> > SummonDungeon::GetPositions()
{
    std::deque< std::pair<int,int> > positionsArray;

    for(auto summon : this->objectArray)
    {
        positionsArray.push_back(summon->GetPosition());
    }

    return positionsArray;
}

void SummonDungeon::SummonObject(rapidjson::Value& object, SDL_Renderer* renderer)
{
    PlayerSummon *summon = new PlayerSummon(object, renderer);
    this->objectArray.push_back(summon);
}