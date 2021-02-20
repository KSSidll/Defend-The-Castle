#pragma once
#include "../Managers/Player.hpp"
#include "Button.hpp"
#include <deque>

class Button;
class Game;

struct EntityMenu
{
    UILabel* NameLabel;
    Button* Button;
};

class GameMenu
{
    private:
        std::unordered_map<std::string, std::string> EntityStatsDict;
        std::unordered_map<std::string, std::string> EntityNameDict;
        std::deque<EntityMenu*> EntityMenus;
        rapidjson::Value* json;
        SDL_Renderer* renderer;
        SummonDungeon* dungeon;
        
        Player* player;
        Game* game;
        SDL_Rect gameInfoBackgroundPos = { 0, 0, 1024, 100 };
        SceneObject* gameInfoBackground;
        UILabel* levelInfo;
        UILabel* playerFujika;
        UILabel* playerFuko;

        SceneObject* enemyInfoBackground;
        UILabel* enemyNameLabel;
        UILabel* enemyInfoLabel;

    public:
        GameMenu( rapidjson::Value* json, SummonDungeon* dungeon, SDL_Renderer* renderer, TextureManager* textureManager, Player* player, Game* game );
        ~GameMenu(){};

        void Render();
        void HandleEvents( SDL_Event* event );
        void Reset( float multiplier );
        void Update();
};