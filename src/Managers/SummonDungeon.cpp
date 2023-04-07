#include "../Objects/PlayerSummon.h"
#include "SummonDungeon.h"
#include "Player.h"
#include "TextureManager.h"

SummonDungeon::SummonDungeon()
{
    textureManager = nullptr;
    renderer = nullptr;
    player = nullptr;
}

SummonDungeon::~SummonDungeon()
{
    player = nullptr;
    renderer = nullptr;
    textureManager = nullptr;
}

void SummonDungeon::KillPending()
{
    for( auto& summon : pendingKills )
    {
        for( int i = 0; i != objectArray.size(); ++i )
        {
            if( objectArray[i].GetId() == summon->GetId() )
            {
                objectArray[i] = objectArray.back();
                objectArray.pop_back();
                --i;
                break;
            }
        }
    }

    pendingKills.clear();
}

void SummonDungeon::KillSummonObject( PlayerSummon* summon )
{
    pendingKills.push_back( summon );
}

SummonDungeon::SummonDungeon( TextureManager* textureManager, SDL_Renderer* renderer, Player* player )
{
    this->textureManager = textureManager;
    this->renderer = renderer;
    this->player = player;
}

void SummonDungeon::Update()
{
    KillPending();

    for( auto& summon : objectArray )
    {
        summon.Update();
        if( summon.KillPending() ) KillSummonObject( &summon );
    }
}

void SummonDungeon::Render()
{
    for( auto& summon : objectArray )
    {
        summon.Render();
    }
}

void SummonDungeon::Reset()
{
    objectArray.clear();
    pendingKills.clear();
    id = 0;
}

void SummonDungeon::SummonObject( rapidjson::Value& object )
{
    if( player->Summon( object["cost"].GetInt() ) )
    {
        objectArray.push_back({textureManager->GetTexture( object["textureSrc"] ), object, renderer, id});
        ++id;
    }
}