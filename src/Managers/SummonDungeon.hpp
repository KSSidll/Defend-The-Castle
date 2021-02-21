#pragma once
#include "../Objects/PlayerSummon.hpp"
#include "Player.hpp"
#include "TextureManager.hpp"
#include <deque>

class SummonDungeon
{
    private:
        TextureManager* textureManager;
        SDL_Renderer* renderer;
        Player* player;

        std::deque<PlayerSummon> objectArray;
        std::deque<PlayerSummon> pendingKills;

        int id = 0;

        void KillPending();
        void KillSummonObject( PlayerSummon summon );

    public:
        SummonDungeon();
        ~SummonDungeon();

        SummonDungeon( TextureManager* textureManager, SDL_Renderer* renderer, Player* player );

        void Update();
        void Render();
        void Reset();
        std::deque<PlayerSummon>& getObjectArray(){ return objectArray; };

        void SummonObject( rapidjson::Value& object );
};