#pragma once
#include "Button.hpp"
#include <deque>

class Button;
class Game;
struct LabeledButton;

class LoseMenu
{
    private:
        Game* game;
        SDL_Renderer* renderer;

        std::deque<LabeledButton> buttons;
        SceneObject background;
        UILabel label;

        SDL_Rect exitButtonPos = { 362,300,300,150 };
        SDL_Rect loadButtonPos = { 362,600,300,100 };
        
    public:
        LoseMenu();
        ~LoseMenu();

        LoseMenu( SDL_Renderer* renderer, Game* game, TextureManager* textureManager );

        void Render();
        void HandleEvents( SDL_Event* event );
};