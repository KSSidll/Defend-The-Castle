#pragma once
#include "PlayerSummon.hpp"
#include <deque>

class SummonDungeon
{
    private:
        std::deque<PlayerSummon*> objectArray;

    public:
        SummonDungeon(){};
        ~SummonDungeon(){};

        void Update();
        void Render();
        std::deque< std::pair<int,int> > GetPositions();
        std::deque<PlayerSummon*> getObjectArray(){ return objectArray; };

        void SummonObject(rapidjson::Value& object, SDL_Renderer* renderer);
        void KillSummonObject(int id);
};