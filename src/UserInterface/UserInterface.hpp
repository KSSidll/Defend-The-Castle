#pragma once
#include "../Managers/SummonDungeon.hpp"
#include "../Managers/TextureManager.hpp"
#include "MainMenu.hpp"
#include "GameMenu.hpp"
#include "PauseMenu.hpp"

class MainMenu;
class GameMenu;
class PauseMenu;
class Game;

class UserInterface
{
private:
    Game* game;
    TextureManager* textureManager;
    GameMenu* gameMenu;
    PauseMenu* pauseMenu;
    MainMenu* mainMenu;

public:
    UserInterface( rapidjson::Value& json, SummonDungeon* dungeon, SDL_Renderer* renderer, TextureManager* textureManager, Game* game );
    ~UserInterface();

    void Render();
    void HandleEvents( SDL_Event* event );
    void Reset( float multiplier );
};