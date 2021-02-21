#pragma once
#include "Button.hpp"
#include <deque>

class Button;
class Game;

class MainMenu
{
    private:
        struct MainMenuButton
        {
            UILabel label;
            Button* button;
        };

        Game* game;
        SDL_Renderer* renderer;

        std::deque<MainMenuButton> buttons;
        SceneObject background;

        UILabel mainMenuLabel;

        SDL_Rect newGameButtonPos = { 362,200,300,150 };
        SDL_Rect continueButtonPos = { 362,400,300,150 };
        SDL_Rect quitButtonPos = { 412,600,200,100 };

    public:
        MainMenu();
        ~MainMenu();

        MainMenu( SDL_Renderer* renderer, TextureManager* textureManager, Game* game );

        void Render();
        void HandleEvents( SDL_Event* event );
};