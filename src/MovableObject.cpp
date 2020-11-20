#include "MovableObject.hpp"

void MovableObject::Update()
{
    
}

void MovableObject::Render()
{
    SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}