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
        rapidjson::Value* json;

        int begin_column = 0;
        int begin_line = 0;

        int column_count = 0;
        int line_count = 0;

        struct itemColumn;
        struct columnLine;
        struct Page;
        Page* fullPage;

        UILabel* mainLabel;
        UILabel* playerInfoLabel;
        UILabel* returnButtonLabel;
        Button* returnButton;
        SceneObject* background;

        Button* col_incButton;
        Button* col_decButton;
        Button* line_incButton;
        Button* line_decButton;
        
    public:
        ShopMenu();
        ~ShopMenu();

        ShopMenu( SDL_Renderer* renderer, Game* game, TextureManager* textureManager, Player* player, rapidjson::Value* json );

        void Reset();

        void Update( bool bStatUpdate = false );
        void Render();
        void HandleEvents( SDL_Event* event, bool* bUpdate );
        void Save( rapidjson::Document* saveJson );
        void Load( rapidjson::Value* saveJson );
};