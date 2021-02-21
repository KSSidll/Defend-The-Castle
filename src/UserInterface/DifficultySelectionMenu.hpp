#pragma once
#include "Button.hpp"
#include <deque>

class Button;
class Game;
struct LabeledButton;

class DifficultySelectionMenu
{
    private:
        Game* game;
        SDL_Renderer* renderer;
        
        std::deque<LabeledButton> buttons;
        SceneObject background;
        UILabel label;

        SDL_Rect easyButtonPos = {412,200,200,100};
        SDL_Rect mediumButtonPos = {412,400,200,100};
        SDL_Rect hardButtonPos = {412,600,200,100};
        
    public:
        DifficultySelectionMenu();
        ~DifficultySelectionMenu();

        DifficultySelectionMenu( SDL_Renderer* renderer, Game* game, TextureManager* textureManager );

        void Render();
        void HandleEvents( SDL_Event* event );
};