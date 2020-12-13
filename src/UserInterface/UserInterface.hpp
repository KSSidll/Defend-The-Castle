#pragma once
#include "../Managers/SummonDungeon.hpp"
#include "../Managers/TextureManager.hpp"
#include "../Managers/Player.hpp"
#include "MainMenu.hpp"
#include "GameMenu.hpp"
#include "PauseMenu.hpp"
#include "DifficultySelectionMenu.hpp"
#include "WinMenu.hpp"
#include "LoseMenu.hpp"
#include "ShopMenu.hpp"

class MainMenu;
class GameMenu;
class PauseMenu;
class DifficultySelectionMenu;
class WinMenu;
class LoseMenu;
class ShopMenu;
class Game;

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

public:
    UserInterface( rapidjson::Value* json, SummonDungeon* dungeon, SDL_Renderer* renderer, TextureManager* textureManager, Game* game, Player* player );
    ~UserInterface();

    void Update();
    void Render();
    void HandleEvents( SDL_Event* event );
    void Reset( float multiplier );
};