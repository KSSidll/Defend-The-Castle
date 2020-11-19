#include "PlayerSummon.hpp"
#include <deque>

class ObjectDungeon
{
    private:
        std::deque<PlayerSummon*> objectArray;

    public:
        ObjectDungeon();
        ~ObjectDungeon();

        void Update();
        void Render();

        void SummonObject(rapidjson::Value& object, SDL_Renderer* renderer);
};