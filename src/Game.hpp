#define SDL_MAIN_HANDLED

#pragma once
#include "SummonDungeon.hpp"
#include "Enemy.hpp"
#include "TextureManager.hpp"

class Game
{
private:
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
    rapidjson::Document objectsDoc;
    SummonDungeon summonDungeon;
    SceneObject* background;
    Enemy* enemy;
    TextureManager* textureManager;

public:
    Game(){};
    ~Game(){};

    void Init(const char* title, int width, int height, bool fullscreen);
    
    void HandleEvents();
    void Update();
    void Render();
    void Clean();
    void HandleCollisions();

    bool Running() { return isRunning; };
};