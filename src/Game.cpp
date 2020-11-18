#include "ObjectDungeon.hpp"

ObjectDungeon objectDungeon;
SDL_Texture *bgTex;

Game::Game()
{

}

Game::~Game()
{

}

void Game::init(const char* title, int width, int height, bool fullscreen)
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

    SDL_Surface* tempBgSurface = IMG_Load(objectsDoc["background"]["textureSrc"].GetString());
    bgTex = SDL_CreateTextureFromSurface(renderer, tempBgSurface);
    SDL_FreeSurface(tempBgSurface);

    objectDungeon.SummonObject(objectsDoc["summons"]["warrior"], renderer);
    
}

void Game::handleEvents()
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

void Game::update()
{
    objectDungeon.Update();
}

void Game::render()
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, bgTex, NULL, NULL);
    objectDungeon.Render();
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}