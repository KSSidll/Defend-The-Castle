#define SDL_MAIN_HANDLED

#pragma once
#include "Global.hpp"
#include "../UserInterface/UserInterface.hpp"
#include "../Objects/Enemy.hpp"
#include "../Managers/TextureManager.hpp"
#include "../Managers/Player.hpp"

#include "rapidjson/filewritestream.h"
#include <rapidjson/writer.h>

class UserInterface;

class Game
{
private:
    float enemyStatsLevelMultiplier = 1.1;
    int level;
    bool menuFlag = true;
    bool isPaused = true;
    bool mainMenu = true;
    bool difficultyMenu = false;
    bool winMenu = false;
    bool loseMenu = false;
    bool shopMenu = false;
    bool isRunning;

    SDL_Window *window;
    SDL_Renderer *renderer;
    rapidjson::Document* objectsDoc;
    rapidjson::Document* saveDoc;
    SummonDungeon* summonDungeon;
    UserInterface* userInterface;
    SceneObject* background;
    Enemy* enemy;
    TextureManager* textureManager;
    Player* player;

    void ResetMenus();

public:
    Game(){};
    ~Game(){};

    void Init( const char* title, int width, int height, bool fullscreen );
    
    void HandleEvents();
    void Update();
    void Render();
    void Clean();
    void HandleCollisions();
    void Reset();
    void Save();
    void Load();
    
    void Pause() { isPaused = true; };
    void UnPause() { isPaused = false; };
    void Quit() { isRunning = false; };
    
    void IncreaseLevel();
    void ChangeEnemyLevelMultiplier( float multiplier );

    bool Running() { return isRunning; };
    bool Paused() { return isPaused; };
    int Level() { return level; };

    void LoseGame();
    void NewGame();
    void Start();
    void MainMenu();
    void WinMenu();
    void ShopMenu();

    bool isMainMenu() { return mainMenu; };
    bool isDifficultyMenu() { return difficultyMenu; };
    bool isWinMenu() { return winMenu; };
    bool isLoseMenu() { return loseMenu; };
    bool isShopMenu() { return shopMenu; };
};