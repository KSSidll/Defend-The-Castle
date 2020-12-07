#pragma once
#include "Button.hpp"
#include <deque>

class GameMenu
{
    private:
        std::deque<Button*> summonButtons;
        rapidjson::Value json;
        SDL_Renderer* renderer;
        SummonDungeon* dungeon;

    public:
        GameMenu( rapidjson::Value& json, SummonDungeon* dungeon, SDL_Renderer* renderer, TextureManager* textureManager );
        ~GameMenu(){};

        void Render();
        void HandleEvents( SDL_Event* event );
};