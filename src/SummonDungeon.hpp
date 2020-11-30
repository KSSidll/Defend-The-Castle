#pragma once
#include "PlayerSummon.hpp"
#include "TextureManager.hpp"
#include <deque>

class SummonDungeon
{
    private:
        std::deque<PlayerSummon*> objectArray;
        std::deque<PlayerSummon*> pendingKills;
        TextureManager* textureManager;

        int id = 0;

        void KillPending();
        void KillSummonObject( PlayerSummon* summon );

    public:
        SummonDungeon( TextureManager* textureManager );
        ~SummonDungeon(){};

        void Update();
        void Render();
        std::deque<PlayerSummon*> getObjectArray(){ return objectArray; };

        void SummonObject( rapidjson::Value& object, SDL_Renderer* renderer);
};