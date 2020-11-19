#include "EntityObject.hpp"

class PlayerSummon : virtual public EntityObject
{
    private:
        int cost;

    public:
        PlayerSummon(){};
        ~PlayerSummon(){};
        PlayerSummon(rapidjson::Value& object, SDL_Renderer* renderer);
};