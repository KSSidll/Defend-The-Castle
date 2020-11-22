#pragma once
#include "SceneObject.hpp"

class MovableObject : public SceneObject
{
    protected:
        int xpos;
        int ypos;
        int movementSkipCount = 0;
        float renderScale;
        bool isMoving = true;
        SDL_Rect srcRect, destRect;
        
    public:
        MovableObject(){};
        ~MovableObject(){};
        MovableObject(rapidjson::Value& object, SDL_Renderer* renderer);

        void Update();
        void Render();
        std::pair<int,int> GetPosition(){ return std::make_pair( destRect.x, destRect.y ); };
};