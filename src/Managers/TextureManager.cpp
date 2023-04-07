#include "TextureManager.h"

TextureManager::TextureManager()
{
    renderer = nullptr;
}

TextureManager::~TextureManager()
{
    renderer = nullptr;
}

TextureManager::TextureManager( SDL_Renderer* renderer )
{
    TTF_Init();
    this->renderer = renderer;

    SDL_Surface* tempSurface = SDL_CreateRGBSurface( 0, 1, 1, 12, 0, 0, 0, 0 );

    SDL_Texture* blackBackground = SDL_CreateTextureFromSurface( renderer, tempSurface );
    textureArray.insert({ "darkBackground", blackBackground });

    SDL_FreeSurface( tempSurface );
}

void TextureManager::LoadTexture( rapidjson::Value& texturePath )
{
    SDL_Surface* tempSurface = IMG_Load( texturePath.GetString() );

    SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, tempSurface );
    textureArray.insert({ texturePath.GetString(), texture });

    SDL_FreeSurface( tempSurface );
}

void TextureManager::LoadTexture( const char* key, const char* filePath )
{
    SDL_Surface* tempSurface = IMG_Load( filePath );

    SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, tempSurface );
    textureArray.insert({ key, texture });

    SDL_FreeSurface( tempSurface );
}

void TextureManager::LoadButtonTexture( const char* key, const char* none, const char* over, const char* down )
{
    SDL_Texture* texture_none = nullptr;
    SDL_Texture* texture_over = nullptr;
    SDL_Texture* texture_down = nullptr;

    SDL_Surface* tempSurface_none = IMG_Load( none );
    texture_none = SDL_CreateTextureFromSurface( renderer, tempSurface_none );
    SDL_FreeSurface( tempSurface_none );

    if( over == none )
        texture_over = texture_none;
    else
    {
        SDL_Surface* tempSurface_over = IMG_Load( over );
        texture_over = SDL_CreateTextureFromSurface( renderer, tempSurface_over );
        SDL_FreeSurface( tempSurface_over );
    }

    if( down == over )
        texture_down = texture_over;
    else
    {
        SDL_Surface* tempSurface_down = IMG_Load( down );
        texture_down = SDL_CreateTextureFromSurface( renderer, tempSurface_down );
        SDL_FreeSurface( tempSurface_down );
    }

    ButtonTextures textures = { texture_none, texture_over, texture_down };

    buttonTextureArray.insert({ key, textures });

}

SDL_Texture* TextureManager::GetTexture( rapidjson::Value& texturePath )
{
    return textureArray.at( texturePath.GetString() );
}

SDL_Texture* TextureManager::GetTexture( const char* key )
{
    return textureArray.at( key );
}

ButtonTextures* TextureManager::GetButtonTexture( const char* key )
{
    return &buttonTextureArray.at( key );
}