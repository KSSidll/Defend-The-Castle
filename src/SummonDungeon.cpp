#include "SummonDungeon.hpp"
#include <iostream>
#include <numeric>
#include <string_view>
#include <bits/stdc++.h>


void SummonDungeon::Update()
{
    KillPending();

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

void SummonDungeon::KillSummonObject(PlayerSummon* summon)
{
    summon->Kill();
    pendingKills.push_back(summon);
}

void SummonDungeon::KillPending()
{
    for(auto const& summon : pendingKills)
    {
        if( summon->KillPending() )
        {
            for(int i = 0; i != objectArray.size(); ++i)
            {
                if(objectArray[i]->GetId() == summon->GetId())
                    objectArray.erase(objectArray.begin() + i);  
            }
            pendingKills.pop_front();
            delete summon;
        }
        
    }
}