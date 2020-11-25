#include "EntityObject.hpp"

EntityObject::EntityObject(SDL_Texture* objTexture, rapidjson::Value& object, SDL_Renderer* renderer) : MovableObject(objTexture, object, renderer)
{
    health = object["health"].GetInt();
    attackDamage = object["attackDamage"].GetInt();
    range = object["range"].GetInt();
    movementSpeed = object["movementSpeed"].GetFloat();
    attackInterval = object["attackInterval"].GetFloat();
    animationSpeed *= movementSpeed * 10;
}

float EntityObject::GetRange()
{
    return range;
}

void EntityObject::Kill()
{
    alive = false;
    isMoving = false;
    animationYpos = animationLengths.size()-1;
    animationSpeed = 20;
    animationXpos = 0;
    animationFramesSkipped = 0;
}

void EntityObject::Render()
{
    isAnimationDone = false;

    SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
    
    if( animationSpeed )
    if( animationFramesSkipped == ANIMATION_SPEED_DIVISOR / (FPS*animationSpeed) )
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