#include "SceneObject.hpp"

SceneObject::SceneObject( SDL_Texture* objTexture, SDL_Renderer* renderer )
{
    this->renderer = renderer;
    this->objTexture = objTexture;
}

SceneObject::SceneObject( SDL_Texture* objTexture, SDL_Renderer* renderer, SDL_Rect position )
{
    this->renderer = renderer;
    this->objTexture = objTexture;
    this->position = position;
    fullScreen = false;
}

void SceneObject::Render()
{
    if( fullScreen )
        SDL_RenderCopy( renderer, objTexture, NULL, NULL );
    else
        SDL_RenderCopy( renderer, objTexture, NULL, &position );
}  