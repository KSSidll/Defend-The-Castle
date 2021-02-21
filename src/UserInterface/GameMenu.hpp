#pragma once
#include "../Managers/Player.hpp"
#include "Button.hpp"
#include <deque>

class Button;
class Game;

class GameMenu
{
    private:
        struct EntityMenu
        {
            UILabel nameLabel;
            UILabel statsLabel;
            Button* button;
        };

        rapidjson::Value* json;
        SDL_Renderer* renderer;
        SummonDungeon* dungeon;
        Player* player;
        Game* game;

        std::unordered_map<std::string, std::string> EntityStatsDict;
        std::unordered_map<std::string, std::string> EntityNameDict;
        std::deque<EntityMenu> EntityMenus;
        
        SDL_Rect gameInfoBackgroundPos = { 0, 0, 1024, 100 };
        SceneObject gameInfoBackground;
        
        UILabel levelInfo;
        UILabel playerFujika;
        UILabel playerFuko;

        SceneObject enemyStatsBackground;
        UILabel enemyNameLabel;
        UILabel enemyStatsLabel;

    public:
        GameMenu();
        ~GameMenu();

        GameMenu( rapidjson::Value* json, SummonDungeon* dungeon, SDL_Renderer* renderer, TextureManager* textureManager, Player* player, Game* game );

        void Render();
        void HandleEvents( SDL_Event* event );
        void Reset( float multiplier );
        void Update();
};