#pragma once
#include "../Objects/PlayerSummon.hpp"
#include "TextureManager.hpp"
#include <deque>

class SummonDungeon
{
    private:
        std::deque<PlayerSummon*> objectArray;
        std::deque<PlayerSummon*> pendingKills;
        TextureManager* textureManager;
        SDL_Renderer* renderer;

        int id = 0;

        void KillPending();
        void KillSummonObject( PlayerSummon* summon );

    public:
        SummonDungeon( TextureManager* textureManager, SDL_Renderer* renderer );
        ~SummonDungeon(){};

        void Update();
        void Render();
        void Reset();
        std::deque<PlayerSummon*> getObjectArray(){ return objectArray; };

        void SummonObject( rapidjson::Value& object );
};