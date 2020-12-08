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

void TextureManager::LoadButtonTexture( const char* key, const char* none, const char* over, const char* down )
{

    SDL_Surface* tempSurface_none = IMG_Load( none );
    SDL_Texture* texture_none = SDL_CreateTextureFromSurface( renderer, tempSurface_none );
    SDL_FreeSurface( tempSurface_none );

    SDL_Surface* tempSurface_over = IMG_Load( over );
    SDL_Texture* texture_over = SDL_CreateTextureFromSurface( renderer, tempSurface_over );
    SDL_FreeSurface( tempSurface_over );

    SDL_Surface* tempSurface_down = IMG_Load( down );
    SDL_Texture* texture_down = SDL_CreateTextureFromSurface( renderer, tempSurface_down );
    SDL_FreeSurface( tempSurface_down );


    ButtonTextures textures = { texture_none, texture_over, texture_down };

    buttonTextureArray.insert({ key, textures });

}

SDL_Texture* TextureManager::GetTexture( rapidjson::Value& texturePath )
{
    return textureArray.at( texturePath.GetString() );
}

ButtonTextures TextureManager::GetButtonTexture( const char* key )
{
    return buttonTextureArray.at( key );
}

SDL_Texture* TextureManager::CreateTextTexture( const char* text, const int size, SDL_Color color )
{
    TTF_Font* Sans = TTF_OpenFont( "assets/fonts/Sans.ttf", size );
    
    SDL_Surface* surfaceText = TTF_RenderText_Solid( Sans, text, color );
    SDL_Texture* Text = SDL_CreateTextureFromSurface( renderer, surfaceText );
    SDL_FreeSurface( surfaceText );

    return Text;
}