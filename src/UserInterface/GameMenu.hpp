#pragma once
#include <SDL2/SDL.h>
#include <rapidjson/document.h>
#include <deque>

struct LabeledButton;

class Button;
class Game;
class SummonDungeon;
class Player;
class TextureManager;
class UILabel;
class SceneObject;

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
        SceneObject* gameInfoBackground;
        
        UILabel* levelInfo;
        UILabel* playerFujika;
        UILabel* playerFuko;

        SceneObject* enemyStatsBackground;
        UILabel* enemyNameLabel;
        UILabel* enemyStatsLabel;

    public:
        GameMenu();
        ~GameMenu();

        GameMenu( rapidjson::Value* json, SummonDungeon* dungeon, SDL_Renderer* renderer, TextureManager* textureManager, Player* player, Game* game );

        void Render();
        void HandleEvents( SDL_Event* event );
        void Reset( float multiplier );
        void Update( bool bStatUpdate = false );
};