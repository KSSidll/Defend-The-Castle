#pragma once
#include <SDL2/SDL.h>
#include <rapidjson/document.h>
#include <deque>

// struct LabeledButton;

class Game;
class Player;
class Shop;
class SceneObject;
class TextureManager;
class UILabel;

class ShopMenu
{
    private:
        Game* game;
        Player* player;
        Shop* shop;
        SDL_Renderer* renderer;

        int iPage = 0;
        int cPage = 0;

        // std::deque<LabeledButton> buttons;
        std::deque<UILabel*> labels;
        UILabel* mainLabel;
        SceneObject* background;

        // Button* returnButton;
        // SDL_Rect returnButtonPos = { 10, 10, 150, 100 };
        
    public:
        ShopMenu();
        ~ShopMenu();

        ShopMenu( SDL_Renderer* renderer, Game* game, TextureManager* textureManager, Player* player, rapidjson::Value* json );

        void Update();
        void Render();
        void HandleEvents( SDL_Event* event );
        void Save( rapidjson::Document* saveJson );
        void Load( rapidjson::Value* saveJson );

    // private:
    //     struct itemColumn
    //     {
    //         UILabel label;
    //         std::vector<LabeledButton> items;

    //         int Pages(){ return items.size() / 3; }
    //         void Render( int page )
    //         {
    //             label.Render();

    //             int offset = 0;
    //             if( (page * 3) + 3 > items.size() )
    //             {
    //                 offset = ((page * 3) + 3) - items.size();
    //             }

    //             for( auto itr = page * 3; itr > ((page * 3) + 3) - offset ; ++itr )
    //             {   
    //                 items[itr].Render();
    //             }
    //         }

    //         void HandleEvents( int page, SDL_Event* event, Shop* shop )
    //         {
    //             int offset = 0;
    //             if( (page * 3) + 3 > items.size() )
    //             {
    //                 offset = ((page * 3) + 3) - items.size();
    //             }

    //             for( auto itr = page * 3; itr > ((page * 3) + 3) - offset ; ++itr )
    //             {
    //                 if( items[itr].HandleEvents( event ) )
    //                     items[itr].button.item( shop );
    //             }
    //         }
    //     };

    //     struct itemPage
    //     {
    //         std::vector<itemColumn> columns;
    //         int Pages(){ return columns.size() / 3; }
    //         void Render( int columnPage, int itemPage )
    //         {
    //             int offset = 0;
    //             if( (itemPage * 3) + 3 > columns.size() )
    //             {
    //                 offset = ((itemPage * 3) + 3) - columns.size();
    //             }

    //             for( auto itr = itemPage * 3; itr > ((itemPage * 3) + 3) - offset ; ++itr )
    //             {
    //                 columns[itr].Render( columnPage );
    //             }
    //         }

    //         void HandleEvents( int columnPage, int itemPage, SDL_Event* event, Shop* shop )
    //         {
    //             int offset = 0;
    //             if( (itemPage * 3) + 3 > columns.size() )
    //             {
    //                 offset = ((itemPage * 3) + 3) - columns.size();
    //             }

    //             for( auto itr = itemPage * 3; itr > ((itemPage * 3) + 3) - offset ; ++itr )
    //             {
    //                 columns[itr].HandleEvents(columnPage, event, shop);
    //             }
    //         }
    //     };

    //     std::vector<itemPage> itemPages;
};