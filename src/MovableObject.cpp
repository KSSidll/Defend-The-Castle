#include "MovableObject.hpp"

MovableObject::MovableObject(SDL_Texture* objTexture, rapidjson::Value& object, SDL_Renderer* renderer) : SceneObject(objTexture, object, renderer)
{
    renderScale = object["renderScale"].GetFloat();

    srcRect.x = object["srcRectX"].GetInt();
    srcRect.y = object["srcRectY"].GetInt();
    srcRect.h = object["srcRectH"].GetInt();
    srcRect.w = object["srcRectW"].GetInt();
    destRect.x = object["destRectX"].GetInt();
    destRect.y = object["destRectY"].GetInt();
    destRect.h = srcRect.h * renderScale;
    destRect.w = srcRect.w * renderScale;

    for (auto& position : object["positions"].GetArray())
        animationLengths.push_back(position.GetInt());
}

void MovableObject::Render()
{
    isAnimationDone = false;

    SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);

    if(animationFramesSkipped == FPS/animationSpeed)
    {
        ++animationXpos;

        srcRect.x = srcRect.w * animationXpos;
        srcRect.y = srcRect.h * animationYpos;

        if(animationXpos == animationLengths[ animationYpos ] -1)
        {
            animationXpos = 0;
            isAnimationDone = true;
        } 
        
        animationFramesSkipped = 0;
    } else ++animationFramesSkipped;
}