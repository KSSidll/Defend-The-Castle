#include "GameObject.hpp"

class ObjectDungeon
{
    private:
        std::deque<GameObject*> objectArray;

    public:
        ObjectDungeon();
        ~ObjectDungeon();

        void Update();
        void Render();

        void SummonObject(rapidjson::Value& object, SDL_Renderer* renderer);
};