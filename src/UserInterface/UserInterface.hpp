#pragma once
#include "../Managers/SummonDungeon.hpp"
#include "../Managers/TextureManager.hpp"
#include "MainMenu.hpp"
#include "GameMenu.hpp"
#include "PauseMenu.hpp"

class UserInterface
{
private:
    const bool* paused;
    TextureManager* textureManager;
    GameMenu* gameMenu;

public:
    UserInterface( rapidjson::Value& json, SummonDungeon* dungeon, SDL_Renderer* renderer, TextureManager* textureManager, const bool* paused );
    ~UserInterface();

    void Render();
    void HandleEvents( SDL_Event* event );
};