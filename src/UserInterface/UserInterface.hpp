#pragma once

class Game;
class GameMenu;
class PauseMenu;
class MainMenu;
class DifficultySelectionMenu;
class WinMenu;
class LoseMenu;
class ShopMenu;

class UserInterface
{
private:
    Game* game;
    GameMenu* gameMenu;
    PauseMenu* pauseMenu;
    MainMenu* mainMenu;
    DifficultySelectionMenu* difficultySelectionMenu;
    WinMenu* winMenu;
    LoseMenu* loseMenu;
    ShopMenu* shopMenu;

    bool bStatUpdate = false;

public:
    UserInterface();
    ~UserInterface();
    
    UserInterface( rapidjson::Value* json, SummonDungeon* dungeon, SDL_Renderer* renderer, TextureManager* textureManager, Game* game, Player* player );

    void Update();
    void Render();
    void HandleEvents( SDL_Event* event );
    void Reset( float multiplier );
    void HardReset();
    void Save( rapidjson::Document* saveJson );
    void Load( rapidjson::Value* saveJson );
};