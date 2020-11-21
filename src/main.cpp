#include "Game.hpp"

Game *game = nullptr;

int main()
{
    const int FPS = 60;
    const double frameDelay = 1000 / FPS;

    bool updateOnly = false;
    Uint32 frameStart;
    int frameTime;

    game = new Game();
    game->Init("SDL", 800, 600, false);

    while (game->Running())
    {
        frameStart = SDL_GetTicks();

        game->HandleEvents();
        game->Update();

        if(!updateOnly)
            game->Render();
        else
            updateOnly = false;

        frameTime = SDL_GetTicks() - frameStart;

        if(frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
        else
            updateOnly = true;
        
    }

    game->Clean();
    return 0;
}