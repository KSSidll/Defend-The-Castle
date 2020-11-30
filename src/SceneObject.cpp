#include "SceneObject.hpp"

SceneObject::SceneObject( SDL_Texture* objTexture ,rapidjson::Value& object, SDL_Renderer* renderer )
{
    this->renderer = renderer;
    this->objTexture = objTexture;
}

void SceneObject::Render()
{
    SDL_RenderCopy( renderer, objTexture, NULL, NULL );
}