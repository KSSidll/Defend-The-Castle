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

    textureManager = new TextureManager(renderer);

    for (auto& texture : objectsDoc["textures"].GetArray())
        textureManager->LoadTexture(texture);

    background = new SceneObject(textureManager->GetTexture(objectsDoc["background"]["textureSrc"]), objectsDoc["background"], renderer);
    enemy = new Enemy(textureManager->GetTexture(objectsDoc["enemy"]["textureSrc"]), objectsDoc["enemy"], renderer);
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
int updateframe = 0;
void Game::Update()
{
    HandleCollisions();

    summonDungeon.Update();
    enemy->Update();

    if(updateframe%75 == 0)  summonDungeon.SummonObject(textureManager->GetTexture(objectsDoc["summons"]["warrior"]["textureSrc"]), objectsDoc["summons"]["warrior"], renderer);
    if(updateframe%120 == 0)  summonDungeon.SummonObject(textureManager->GetTexture(objectsDoc["summons"]["tank"]["textureSrc"]), objectsDoc["summons"]["tank"], renderer);
    if(updateframe%190 == 0)  summonDungeon.SummonObject(textureManager->GetTexture(objectsDoc["summons"]["archer"]["textureSrc"]), objectsDoc["summons"]["archer"], renderer);

    ++updateframe;
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

void Game::HandleCollisions()
{
    for(auto const &summon : summonDungeon.getObjectArray())
    {
        if( summon->Alive() && enemy->Alive() )
        if( summon->GetPosition() + summon->GetRange() > enemy->GetPosition() )
        {
            summon->EnemyCollision();
            summonDungeon.KillSummonObject(summon);
            enemy->Attack();
        }
    }
}