#include "TextureManager.hpp"

TextureManager::TextureManager( SDL_Renderer* renderer )
{
    this->renderer = renderer;
}

void TextureManager::LoadTexture( rapidjson::Value& texturePath )
{
    SDL_Surface* tempSurface = IMG_Load( texturePath.GetString() );

    SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, tempSurface );
    textureArray.insert({ texturePath.GetString(), texture });

    SDL_FreeSurface( tempSurface );
}

SDL_Texture* TextureManager::GetTexture( rapidjson::Value& texturePath )
{
    return textureArray.at( texturePath.GetString() );
}