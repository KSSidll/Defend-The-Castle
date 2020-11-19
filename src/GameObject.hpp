#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"

class GameObject
{
    protected:
        int xpos;
        int ypos;
        float renderScale;

        int health;
        int attackDamage;
        float movementSpeed;
        float attackInterval;
        float range;

        float timeSinceLastAttack = attackInterval / 2;

        SDL_Texture* objTexture;
        SDL_Rect srcRect, destRect;
        SDL_Renderer* renderer;

    public:
        GameObject(){};
        GameObject(rapidjson::Value& object, SDL_Renderer* renderer);
        ~GameObject();

        void Update();
        void Render();
};