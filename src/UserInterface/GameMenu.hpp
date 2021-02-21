#pragma once
#include "../Managers/Player.hpp"
#include "Button.hpp"
#include <deque>

class Button;
class Game;
struct LabeledButton;

class GameMenu
{
    private:
        rapidjson::Value* json;
        SDL_Renderer* renderer;
        SummonDungeon* dungeon;
        Player* player;
        Game* game;

        std::deque<LabeledButton> buttons;
        
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