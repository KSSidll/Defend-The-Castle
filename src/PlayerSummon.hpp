#include "GameObject.hpp"

class PlayerSummon : public GameObject
{
    private:
        int cost;

    public:
        PlayerSummon(rapidjson::Value& object, SDL_Renderer* renderer);
        ~PlayerSummon();
};