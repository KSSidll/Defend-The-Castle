#pragma once
#include "Button.hpp"
#include <deque>

class Button;
class Game;

class PauseMenu
{
    private:
        Game* game;
        std::deque<Button*> buttons;
        SDL_Renderer* renderer;
        TextureManager* textureManager;
        SceneObject* background;
        UILabel* label;

        SDL_Rect resumeButtonPos = {412,200,200,100};
        SDL_Rect quitButtonPos = {412,400,200,100};
        
    public:
        PauseMenu( SDL_Renderer* renderer, Game* game, TextureManager* textureManager );
        ~PauseMenu(){};

        void Render();
        void HandleEvents( SDL_Event* event );
};