#pragma once
#include "../Engine/Global.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"

class SceneObject
{
    protected:
        SDL_Texture* objTexture;
        SDL_Renderer* renderer;
        SDL_Rect position;
        bool fullScreen = true;

    public:
        SceneObject(){};
        ~SceneObject(){};
        SceneObject( SDL_Texture* objTexture, SDL_Renderer* renderer, SDL_Rect position );
        SceneObject( SDL_Texture* objTexture, SDL_Renderer* renderer );

        void Render();
};