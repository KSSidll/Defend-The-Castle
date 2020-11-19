#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"

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