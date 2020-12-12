#pragma once
#include "Button.hpp"
#include <deque>

class Button;
class Game;

class ShopMenu
{
    private:
        Game* game;
        std::deque<Button*> buttons;
        SDL_Renderer* renderer;
        SceneObject* background;
        UILabel* label;

        UILabel* warriorLabel;
        UILabel* tankLabel;
        UILabel* archerLabel;

        SDL_Rect backButtonPos = { 10, 10, 150, 100 };
        
    public:
        ShopMenu( SDL_Renderer* renderer, Game* game, TextureManager* textureManager );
        ~ShopMenu(){};

        void Render();
        void HandleEvents( SDL_Event* event );
};
