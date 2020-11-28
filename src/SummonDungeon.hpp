#pragma once
#include "PlayerSummon.hpp"
#include <deque>

class SummonDungeon
{
    private:
        std::deque<PlayerSummon*> objectArray;
        std::deque<PlayerSummon*> pendingKills;
        int id = 0;

        void KillPending();
        void KillSummonObject(PlayerSummon* summon);

    public:
        SummonDungeon(){};
        ~SummonDungeon(){};

        void Update();
        void Render();
        std::deque<PlayerSummon*> getObjectArray(){ return objectArray; };

        void SummonObject(SDL_Texture* objTexture, rapidjson::Value& object, SDL_Renderer* renderer);
};