#include "SummonDungeon.hpp"
#include <iostream>
#include <numeric>
#include <string_view>
#include <bits/stdc++.h>

void SummonDungeon::KillPending()
{
    for( auto const summon : pendingKills )
    {
        for( int i = 0; i != objectArray.size(); ++i )
        {
            if( objectArray[i]->GetId() == summon->GetId() )
                objectArray.erase( objectArray.begin() + i );
                --i;  
        }
        pendingKills.pop_front();
        delete summon;
    }
}

void SummonDungeon::KillSummonObject( PlayerSummon* summon )
{
    pendingKills.push_back( summon );
}

SummonDungeon::SummonDungeon( TextureManager* textureManager, SDL_Renderer* renderer )
{
    this->textureManager = textureManager;
    this->renderer = renderer;
}

void SummonDungeon::Update()
{
    KillPending();

    for( auto summon : objectArray )
    {
        summon->Update();
        if( summon->KillPending() ) KillSummonObject( summon );
    }
}

void SummonDungeon::Render()
{
    for( auto summon : objectArray )
    {
        summon->Render();
    }
}

void SummonDungeon::SummonObject( rapidjson::Value& object )
{
    PlayerSummon *summon = new PlayerSummon( textureManager->GetTexture( object["textureSrc"] ), object, renderer, id );
    objectArray.push_back( summon );
    ++id;
}