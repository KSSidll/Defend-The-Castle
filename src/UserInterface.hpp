#pragma once
#include "SummonDungeon.hpp"
#include "TextureManager.hpp"
#include "SummonButton.hpp"
#include <unordered_map>

class UserInterface
{
private:
    std::deque<Button> buttons;
    SDL_Renderer* renderer;
    SummonDungeon* dungeon;
    TextureManager* textureManager;
    std::unordered_map< const char*, rapidjson::Document > map;

public:
    UserInterface( rapidjson::Value& json, SummonDungeon* dungeon, SDL_Renderer* renderer, TextureManager* textureManager );
    ~UserInterface();

    void Render();
    void HandleEvents( SDL_Event event );
};