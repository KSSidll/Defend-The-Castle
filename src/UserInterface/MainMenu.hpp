#pragma once
#include "Button.hpp"
#include <deque>

class Button;
class Game;

class MainMenu
{
    private:
        Game* game;
        SDL_Renderer* renderer;
        std::deque<Button*> buttons;
        SceneObject* background;

        UILabel* mainMenuLabel;

        SDL_Rect newGameButtonPos = { 362,200,300,150 };
        SDL_Rect continueButtonPos = { 362,400,300,150 };
        SDL_Rect quitButtonPos = { 412,600,200,100 };

    public:
        MainMenu( SDL_Renderer* renderer, TextureManager* textureManager, Game* game );
        ~MainMenu(){};

        void Render();
        void HandleEvents( SDL_Event* event );
};