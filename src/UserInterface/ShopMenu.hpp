#pragma once
#include <SDL2/SDL.h>
#include <rapidjson/document.h>
#include <deque>

class Game;
class Player;
class Shop;
class SceneObject;
class TextureManager;
class UILabel;
class Button;

class ShopMenu
{
    private:
        Game* game;
        Player* player;
        Shop* shop;
        SDL_Renderer* renderer;

        int iPage = 0;
        int cPage = 0;

        struct itemColumn;
        struct itemPage;
        std::deque<itemPage> itemPages;

        std::deque<UILabel*> labels;
        UILabel* mainLabel;
        SceneObject* background;

        Button* returnButton;
        SDL_Rect returnButtonPos = { 10, 10, 150, 100 };
        
    public:
        ShopMenu();
        ~ShopMenu();

        ShopMenu( SDL_Renderer* renderer, Game* game, TextureManager* textureManager, Player* player, rapidjson::Value* json );

        void Update();
        void Render();
        void HandleEvents( SDL_Event* event );
        void Save( rapidjson::Document* saveJson );
        void Load( rapidjson::Value* saveJson );
};