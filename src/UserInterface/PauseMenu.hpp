#pragma once
#include "Button.hpp"
#include <deque>

class Button;
class Game;

class PauseMenu
{
    private:
        struct PauseMenuButton
        {
            UILabel label;
            Button* button;
        };

        Game* game;
        SDL_Renderer* renderer;

        std::deque<PauseMenuButton> buttons;
        SceneObject background;
        UILabel label;

        SDL_Rect resumeButtonPos = {412,200,200,100};
        SDL_Rect exitButtonPos = {412,400,200,100};
        
    public:
        PauseMenu();
        ~PauseMenu();

        PauseMenu( SDL_Renderer* renderer, Game* game, TextureManager* textureManager );

        void Render();
        void HandleEvents( SDL_Event* event );
};