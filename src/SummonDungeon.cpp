#include "SummonDungeon.hpp"

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
        int id = summon->GetId();
        summon->Render();
    }
}

std::deque< std::pair<int,int> > SummonDungeon::GetPositions()
{
    std::deque< std::pair<int,int> > positionsArray;

    for(auto summon : objectArray)
    {
        positionsArray.push_back(summon->GetPosition());
    }

    return positionsArray;
}

void SummonDungeon::SummonObject(rapidjson::Value& object, SDL_Renderer* renderer)
{
    PlayerSummon *summon = new PlayerSummon(object, renderer, objectArray.size());
    objectArray.push_back(summon);
}

void SummonDungeon::KillSummonObject(int id)
{
    int sie = objectArray.size()-1;
    //std::swap(objectArray.at(id),objectArray.at(sie));
    objectArray.pop_front();
}