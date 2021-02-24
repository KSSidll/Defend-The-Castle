#define SDL_MAIN_HANDLED
#pragma once
#include <SDL2/SDL.h>
#include <rapidjson/document.h>

class SummonDungeon;
class TextureManager;
class UserInterface;
class Player;
class Enemy;
class SceneObject;

class Game
{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    rapidjson::Document* objectsDoc;
    rapidjson::Document* saveDoc;
    SummonDungeon* summonDungeon;
    TextureManager* textureManager;
    UserInterface* userInterface;
    Player* player;
    Enemy* enemy;
    SceneObject* background;

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

    void ResetMenus();

public:
    Game();
    ~Game();

    void Init( const char* title, int width, int height, bool fullscreen );
    
    void HandleEvents();
    void Update();
    void Render();
    void Clean();
    void HandleCollisions();
    void HardReset();
    void Reset();
    void Save(bool incrementLevel = false);
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