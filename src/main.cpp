#include "Game.hpp"

Game *game = nullptr;

int main()
{
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    bool updateOnly = false;
    Uint32 frameStart;
    int frameTime;

    game = new Game();
    game->init("SDL", 800, 600, false);

    while (game->running())
    {
        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();

        if(!updateOnly)
            game->render();
        else
            updateOnly = false;


        frameTime = SDL_GetTicks() - frameStart;

        if(frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
        else
            updateOnly = true;
        
    }

    game->clean();
    return 0;
}