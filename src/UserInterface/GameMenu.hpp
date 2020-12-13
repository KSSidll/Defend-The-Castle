#pragma once
#include "../Managers/Player.hpp"
#include "Button.hpp"
#include <deque>

class Button;
class Game;

// TBD - Make this modular 
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
        // std::deque<SummonButton*> summonButtons;
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

        int summonButtonWidth = 256;

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
        
        SDL_Rect enemyRect = { 3 * summonButtonWidth, 543, summonButtonWidth, 225 };
        std::string enemyLabelText = "";
        UILabel* enemyNameLabel;
        UILabel* enemyLabel;
        SceneObject* enemyLabelBackground;

    public:
        GameMenu( rapidjson::Value* json, SummonDungeon* dungeon, SDL_Renderer* renderer, TextureManager* textureManager, Player* player, Game* game );
        ~GameMenu(){};

        void Render();
        void HandleEvents( SDL_Event* event );
        void Reset( float multiplier );
        void Update();
};