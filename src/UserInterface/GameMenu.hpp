#pragma once
#include "Button.hpp"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include <deque>

class GameMenu
{
    private:
        std::deque<Button*> summonButtons;
        rapidjson::Value json;
        SDL_Renderer* renderer;
        SummonDungeon* dungeon;

        SDL_Rect warriorRect = { 0,543,256,225 };
        std::string warriorLabelText = "";
        UILabel* warriorNameLabel;
        UILabel* warriorLabel;

        SDL_Rect tankRect = { 256,543,256,225 };
        std::string tankLabelText = "";
        UILabel* tankNameLabel;
        UILabel* tankLabel;

        SDL_Rect archerRect = { 512,543,256,225 };
        std::string archerLabelText = "";
        UILabel* archerNameLabel;
        UILabel* archerLabel;

        SDL_Rect enemyRect = { 768,543,256,225 };
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