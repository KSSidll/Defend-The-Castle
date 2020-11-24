#pragma once
#include "PlayerSummon.hpp"
#include <deque>

class SummonDungeon
{
    private:
        std::deque<PlayerSummon*> objectArray;
        int id = 0;

    public:
        SummonDungeon(){};
        ~SummonDungeon(){};

        void Update();
        void Render();
        std::deque<PlayerSummon*> getObjectArray(){ return objectArray; };

        void SummonObject(SDL_Texture* objTexture, rapidjson::Value& object, SDL_Renderer* renderer);
        void KillSummonObject(PlayerSummon* summon);
};