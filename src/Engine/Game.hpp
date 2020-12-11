#define SDL_MAIN_HANDLED

#pragma once
#include "Global.hpp"
#include "../UserInterface/UserInterface.hpp"
#include "../Objects/Enemy.hpp"
#include "../Managers/TextureManager.hpp"

class UserInterface;

class Game
{
private:
    bool isPaused = false;
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
    rapidjson::Document objectsDoc;
    SummonDungeon* summonDungeon;
    UserInterface* userInterface;
    SceneObject* background;
    Enemy* enemy;
    TextureManager* textureManager;

public:
    Game(){};
    ~Game(){};

    void Init( const char* title, int width, int height, bool fullscreen );
    
    void HandleEvents();
    void Update();
    void Render();
    void Clean();
    void HandleCollisions();
    void Pause() { isPaused = true; };
    void UnPause() { isPaused = false; };
    void Quit() { isRunning = false; };

    bool Running() { return isRunning; };
    bool Paused() { return isPaused; };
};