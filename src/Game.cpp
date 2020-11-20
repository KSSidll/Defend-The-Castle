#include "Game.hpp"

void Game::Init(const char* title, int width, int height, bool fullscreen)
{
    int flags = 0;
    if(fullscreen) flags = SDL_WINDOW_FULLSCREEN;

    FILE* objectsJsonFile = fopen("build/assets/objects.json", "r");
    char* readBuffer = new char[65536];
    rapidjson::FileReadStream objectsJson(objectsJsonFile, readBuffer, sizeof(readBuffer));
    objectsDoc.ParseStream(objectsJson);
    delete[] readBuffer;
    fclose(objectsJsonFile);

    if(!SDL_Init(SDL_INIT_EVERYTHING))
    {
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, width, height, flags);

        renderer = SDL_CreateRenderer(window, -1, 0);

        if(renderer)
        {
            SDL_SetRenderDrawColor(renderer, 50,50,50,255);
        } 

        isRunning = true;
    }
    else
    {
        isRunning = false;
    }

    background = new SceneObject(objectsDoc["background"], renderer);
    summonDungeon.SummonObject(objectsDoc["summons"]["warrior"], renderer);
    enemy = new Enemy(objectsDoc["enemy"], renderer);
}

void Game::HandleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    
    default:
        break;
    }
}

void Game::Update()
{
    summonDungeon.Update();
    enemy->Update();
}

void Game::Render()
{
    SDL_RenderClear(renderer);
    background->Render();
    summonDungeon.Render();
    enemy->Render();
    SDL_RenderPresent(renderer);
}

void Game::Clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}