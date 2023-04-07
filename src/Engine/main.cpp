#include "Game.h"
#include "Global.h"

int main()
{
    bool updateOnly = false;
    Uint32 frameStart;
    int frameTime;

    Game* game = new Game();
    game->Init( "Defend The Castle", 1024, 768, false );

    while ( game->Running() )
    {
        frameStart = SDL_GetTicks();

        game->HandleEvents();
        game->Update();

        if( !updateOnly )
            game->Render();
        else
            updateOnly = false;

        frameTime = SDL_GetTicks() - frameStart;

        if( FRAME_DELAY > frameTime )
            SDL_Delay( FRAME_DELAY - frameTime );
        else
            updateOnly = true;
    }

    game->Clean();
    return 0;
}