#pragma once
#include "../Managers/SummonDungeon.hpp"
#include "../Managers/TextureManager.hpp"
#include "MainMenu.hpp"
#include "GameMenu.hpp"
#include "PauseMenu.hpp"
#include "DifficultySelectionMenu.hpp"

class MainMenu;
class GameMenu;
class PauseMenu;
class DifficultySelectionMenu;
class Game;

class UserInterface
{
private:
    Game* game;
    GameMenu* gameMenu;
    PauseMenu* pauseMenu;
    MainMenu* mainMenu;
    DifficultySelectionMenu* difficultySelectionMenu;

public:
    UserInterface( rapidjson::Value& json, SummonDungeon* dungeon, SDL_Renderer* renderer, TextureManager* textureManager, Game* game );
    ~UserInterface();

    void Render();
    void HandleEvents( SDL_Event* event );
    void Reset( float multiplier );
};