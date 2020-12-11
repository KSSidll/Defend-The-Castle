#pragma once
#include "Button.hpp"
#include <deque>

class Button;
class Game;

class LoseMenu
{
    private:
        Game* game;
        std::deque<Button*> buttons;
        SDL_Renderer* renderer;
        SceneObject* background;
        UILabel* label;

        SDL_Rect exitButtonPos = { 362,300,300,150 };
        SDL_Rect loadButtonPos = { 362,600,300,100 };
        
    public:
        LoseMenu( SDL_Renderer* renderer, Game* game, TextureManager* textureManager );
        ~LoseMenu(){};

        void Render();
        void HandleEvents( SDL_Event* event );
};