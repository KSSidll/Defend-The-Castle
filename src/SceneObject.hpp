#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"

class SceneObject
{
    protected:
        SDL_Texture* objTexture;
        SDL_Renderer* renderer;

    public:
        SceneObject(){};
        ~SceneObject(){};
        SceneObject(SDL_Texture* objTexture ,rapidjson::Value& object, SDL_Renderer* renderer);

        void Render();
};