#pragma once
#include "Button.hpp"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include <deque>

class Button;

// struct SummonButton
// {
//     SDL_Rect Position;
//     UILabel* NameLabel;
//     std::deque<UILabel*> Labels;
// };

class GameMenu
{
    private:
        std::deque<Button*> summonButtons;
        // std::deque<SummonButton> summonButton;
        rapidjson::Value json;
        SDL_Renderer* renderer;
        SummonDungeon* dungeon;
        int summonButtonWidth = 256;
        int summonButtonCount = 3;

        SDL_Rect warriorRect = { 0 * summonButtonWidth, 543, summonButtonWidth, 225 };
        std::string warriorLabelText = "";
        UILabel* warriorNameLabel;
        UILabel* warriorLabel;

        SDL_Rect tankRect = { 1 * summonButtonWidth, 543, summonButtonWidth, 225 };
        std::string tankLabelText = "";
        UILabel* tankNameLabel;
        UILabel* tankLabel;

        SDL_Rect archerRect = { 2 * summonButtonWidth, 543, summonButtonWidth, 225 };
        std::string archerLabelText = "";
        UILabel* archerNameLabel;
        UILabel* archerLabel;

        SDL_Rect enemyRect = { summonButtonCount * summonButtonWidth, 543, summonButtonWidth, 225 };
        std::string enemyLabelText = "";
        UILabel* enemyNameLabel;
        UILabel* enemyLabel;
        SceneObject* enemyLabelBackground;

    public:
        GameMenu( rapidjson::Value& json, SummonDungeon* dungeon, SDL_Renderer* renderer, TextureManager* textureManager );
        ~GameMenu(){};

        void Render();
        void HandleEvents( SDL_Event* event );
};