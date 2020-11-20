#pragma once
#include "SceneObject.hpp"

class MovableObject : public SceneObject
{
    protected:
        int xpos;
        int ypos;
        int movementSkipCount = 0;
        float renderScale;
        SDL_Rect srcRect, destRect;
        
    public:
        MovableObject(){};
        ~MovableObject(){};

        void Update();
        void Render();
        std::pair<int,int> GetPosition();
};