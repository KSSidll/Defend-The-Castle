#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include <bits/stdc++.h>

class TextureManager
{
    private:
        std::map< std::string, SDL_Texture* > textureArray;
        SDL_Renderer* renderer;

    public:
        TextureManager(SDL_Renderer* renderer);
        ~TextureManager(){};
        
        void LoadTexture(rapidjson::Value& texturePath);
        SDL_Texture* GetTexture(rapidjson::Value& texturePath);
};