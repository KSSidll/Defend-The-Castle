#include "MovableObject.hpp"

void MovableObject::Update()
{
    
}

void MovableObject::Render()
{
    SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}

std::pair<int,int> MovableObject::GetPosition()
{
    return std::make_pair( destRect.x, destRect.y );
}