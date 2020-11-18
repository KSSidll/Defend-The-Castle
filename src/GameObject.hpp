#include "Game.hpp"

class GameObject
{
    private:
        int xpos;
        int ypos;
        float renderScale;

        SDL_Texture* objTexture;
        SDL_Rect srcRect, destRect;
        SDL_Renderer* renderer;

    public:
        GameObject(rapidjson::Value& object, SDL_Renderer* renderer);
        ~GameObject();

        void Update();
        void Render();
};
