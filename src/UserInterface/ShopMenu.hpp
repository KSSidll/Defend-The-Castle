#pragma once
#include "../Managers/Player.hpp"
#include "../Managers/Shop.hpp"
#include "Button.hpp"
#include <deque>

class Button;
class Game;
struct LabeledButton;
class ShopMenu
{
    private:
        Game* game;
        SDL_Renderer* renderer;
        Player* player;
        Shop* shop;

        std::deque<LabeledButton> buttons;
        std::deque<UILabel> labels;
        UILabel mainLabel;
        SceneObject background;

        std::unordered_map< std::string, std::string > dictionary;

        UILabel* playerInfoLabel;
        UILabel* warriorLabel;
        UILabel* tankLabel;
        UILabel* archerLabel;

        UILabel* spearItemName;
        UILabel* armorItemName;
        UILabel* bowItemName;

        UILabel* spearItemLabel;
        UILabel* armorItemLabel;
        UILabel* bowItemLabel;

        Item* spear;
        Item* armor;
        Item* bow;

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
