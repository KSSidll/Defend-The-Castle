#include "Game.hpp"

int main()
{
    bool updateOnly = false;
    Uint32 frameStart;
    int frameTime;

    Game* game = new Game();
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