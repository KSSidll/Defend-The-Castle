#pragma once
#include "Button.hpp"
#include <deque>

class Button;
class Game;

class WinMenu
{
    private:
        struct WinMenuButton
        {
            UILabel label;
            Button* button;
        };

        Game* game;
        SDL_Renderer* renderer;

        std::deque<WinMenuButton> buttons;
        SceneObject background;
        UILabel label;

        SDL_Rect saveButtonPos = {156,334,200,100};
        SDL_Rect shopButtonPos = {412,334,200,100};
        SDL_Rect nextLevelButtonPos = {668,334,200,100};
        
    public:
        WinMenu();
        ~WinMenu();

        WinMenu( SDL_Renderer* renderer, Game* game, TextureManager* textureManager );

        void Render();
        void HandleEvents( SDL_Event* event );
};