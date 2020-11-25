#pragma once
#include "SceneObject.hpp"
#include <vector>

class MovableObject : public SceneObject
{
    protected:
        int movementVector = 1;
        int xpos;
        int ypos;
        int animationFramesSkipped = 0;
        int animationYpos = 0;
        int animationXpos = 0;
        int animationSpeed = 5;

        float renderScale;
        float xShift = 0;

        bool isMoving = true;
        bool isAnimationDone = false;

        SDL_Rect srcRect, destRect;
        std::vector<int> animationLengths;

        void Move();
        
    public:
        MovableObject(){};
        ~MovableObject(){};
        MovableObject(SDL_Texture* objTexture, rapidjson::Value& object, SDL_Renderer* renderer);

        void Update();
        void Render();
        int GetPosition(){ return destRect.x; };
};