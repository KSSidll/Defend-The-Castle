#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include <bits/stdc++.h>

struct ButtonTextures
{
    SDL_Texture* none;
    SDL_Texture* over;
    SDL_Texture* down;
};

class TextureManager
{
    private:
        std::map< std::string, SDL_Texture* > textureArray;
        std::map< std::string, ButtonTextures > buttonTextureArray;
        SDL_Renderer* renderer;

    public:
        TextureManager( SDL_Renderer* renderer );
        ~TextureManager(){};
        
        void LoadTexture( rapidjson::Value& texturePath );
        void LoadButtonTexture( const char* key, const char* none, const char* over, const char* down );
        SDL_Texture* GetTexture( rapidjson::Value& texturePath );
        ButtonTextures GetButtonTexture( const char* key );
        SDL_Texture* CreateTextTexture( const char* text, const int size, SDL_Color color );
};