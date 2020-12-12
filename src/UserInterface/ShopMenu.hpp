#pragma once
#include "../Managers/Player.hpp"
#include "../Managers/Shop.hpp"
#include "Button.hpp"
#include <deque>

class Button;
class Game;

class ShopMenu
{
    private:
        Game* game;
        Shop shop;
        std::deque<Button*> buttons;
        SDL_Renderer* renderer;
        Player* player;
        SceneObject* background;
        UILabel* label;

        UILabel* playerInfoLabel;
        UILabel* warriorLabel;
        UILabel* tankLabel;
        UILabel* archerLabel;

        SDL_Rect backButtonPos = { 10, 10, 150, 100 };
        
    public:
        ShopMenu( SDL_Renderer* renderer, Game* game, TextureManager* textureManager, Player* player );
        ~ShopMenu(){};

        void Update();
        void Render();
        void HandleEvents( SDL_Event* event );
};
