#pragma once
#include "../Objects/PlayerSummon.hpp"
#include "Player.hpp"
#include "TextureManager.hpp"
#include <deque>

class SummonDungeon
{
    private:
        std::deque<PlayerSummon*> objectArray;
        std::deque<PlayerSummon*> pendingKills;
        TextureManager* textureManager;
        SDL_Renderer* renderer;
        Player* player;

        int id = 0;

        void KillPending();
        void KillSummonObject( PlayerSummon* summon );

    public:
        SummonDungeon( TextureManager* textureManager, SDL_Renderer* renderer, Player* player );
        ~SummonDungeon(){};

        void Update();
        void Render();
        void Reset();
        std::deque<PlayerSummon*> getObjectArray(){ return objectArray; };

        void SummonObject( rapidjson::Value& object );
};