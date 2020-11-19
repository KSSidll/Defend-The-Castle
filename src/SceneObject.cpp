#include "SceneObject.hpp"

SceneObject::SceneObject(rapidjson::Value& object, SDL_Renderer* renderer)
{
    this->renderer = renderer;

    SDL_Surface* tempSurface = IMG_Load(object["textureSrc"].GetString());
    objTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
}

void SceneObject::Render()
{
    SDL_RenderCopy(renderer, objTexture, NULL, NULL);
}