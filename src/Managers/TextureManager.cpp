#include "TextureManager.hpp"

TextureManager::TextureManager( SDL_Renderer* renderer )
{
    TTF_Init();
    this->renderer = renderer;
}

void TextureManager::LoadTexture( rapidjson::Value& texturePath )
{
    SDL_Surface* tempSurface = IMG_Load( texturePath.GetString() );

    SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, tempSurface );
    textureArray.insert({ texturePath.GetString(), texture });

    SDL_FreeSurface( tempSurface );
}

void TextureManager::LoadTexture( const char* key, const char* texturePath )
{
    SDL_Surface* tempSurface = IMG_Load( texturePath );

    SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, tempSurface );
    textureArray.insert({ key, texture });

    SDL_FreeSurface( tempSurface );
}

SDL_Texture* TextureManager::GetTexture( rapidjson::Value& texturePath )
{
    return textureArray.at( texturePath.GetString() );
}

SDL_Texture* TextureManager::GetTexture( const char* key )
{
    return textureArray.at( key );
}

SDL_Texture* TextureManager::CreateTextTexture( const char* text, const int size, SDL_Color color )
{
    TTF_Font* Sans = TTF_OpenFont( "assets/fonts/Sans.ttf", size );
    
    SDL_Surface* surfaceText = TTF_RenderText_Solid( Sans, text, color );
    SDL_Texture* Text = SDL_CreateTextureFromSurface( renderer, surfaceText );
    SDL_FreeSurface( surfaceText );

    return Text;
}