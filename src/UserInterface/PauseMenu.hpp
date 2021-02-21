#pragma once
#include "Button.hpp"
#include <deque>

class Button;
class Game;
struct LabeledButton;

class PauseMenu
{
    private:
        Game* game;
        SDL_Renderer* renderer;

        std::deque<LabeledButton> buttons;
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