#include "UserInterface.hpp"

UserInterface::UserInterface( rapidjson::Value& json, SummonDungeon* dungeon, SDL_Renderer* renderer, TextureManager* textureManager, const bool* paused, Game* game )
{
    this->paused = paused;
    this->textureManager = textureManager;

    gameMenu = new GameMenu( json, dungeon, renderer, textureManager );
    pauseMenu = new PauseMenu( renderer, game, textureManager );

}

void UserInterface::Render()
{
    if( !*paused )
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
    if( !*paused )
    {
        gameMenu->HandleEvents( event );
    }
    else
    {
        pauseMenu->HandleEvents( event );
    }
}