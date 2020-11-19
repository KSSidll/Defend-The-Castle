#pragma once
#include "SceneObject.hpp"

class MovableObject : public SceneObject
{
    protected:
        int xpos;
        int ypos;
        float renderScale;
        SDL_Rect srcRect, destRect;
        
    public:
        MovableObject(){};
        ~MovableObject(){};
        MovableObject(rapidjson::Value& object, SDL_Renderer* renderer);

        void Update();
        void Render();
};