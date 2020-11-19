#include "MovableObject.hpp"

MovableObject::MovableObject(rapidjson::Value& object, SDL_Renderer* renderer)
{
    this->renderer = renderer;

    SDL_Surface* tempSurface = IMG_Load(object["textureSrc"].GetString());
    objTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    renderScale = object["renderScale"].GetFloat();

    srcRect.x = object["srcRectX"].GetInt();
    srcRect.y = object["srcRectY"].GetInt();
    srcRect.h = object["srcRectH"].GetInt();
    srcRect.w = object["srcRectW"].GetInt();
    destRect.x = object["destRectX"].GetInt();
    destRect.y = object["destRectY"].GetInt();
    destRect.h = srcRect.h * renderScale;
    destRect.w = srcRect.w * renderScale;
}

void MovableObject::Update()
{
    
}

void MovableObject::Render()
{
    SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}