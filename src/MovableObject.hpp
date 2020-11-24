#pragma once
#include "SceneObject.hpp"

class MovableObject : public SceneObject
{
    protected:
        int xpos;
        int ypos;
        float renderScale;
        float xShift;
        bool isMoving = true;
        SDL_Rect srcRect, destRect;
        
    public:
        MovableObject(){};
        ~MovableObject(){};
        MovableObject(SDL_Texture* objTexture, rapidjson::Value& object, SDL_Renderer* renderer);

        void Render();
        int GetPosition(){ return destRect.x; };
};