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

        void SummonObject(rapidjson::Value& object, SDL_Renderer* renderer);
};