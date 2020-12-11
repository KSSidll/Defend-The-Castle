#include "UserInterface.hpp"

UserInterface::UserInterface( rapidjson::Value& json, SummonDungeon* dungeon, SDL_Renderer* renderer, TextureManager* textureManager, Game* game )
{
    this->game = game;
    this->textureManager = textureManager;

    gameMenu = new GameMenu( json, dungeon, renderer, textureManager );
    pauseMenu = new PauseMenu( renderer, game, textureManager );

}

void UserInterface::Render()
{
    if( !game->Paused() )
    {
        gameMenu->Render();
    }
    else
    {
        pauseMenu->Render();
    }
}

void UserInterface::HandleEvents( SDL_Event* event )
{
    if( !game->Paused() )
    {
        gameMenu->HandleEvents( event );
    }
    else
    {
        pauseMenu->HandleEvents( event );
    }
}