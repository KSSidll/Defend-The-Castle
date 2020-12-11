#include "UserInterface.hpp"

UserInterface::UserInterface( rapidjson::Value& json, SummonDungeon* dungeon, SDL_Renderer* renderer, TextureManager* textureManager, Game* game )
{
    this->game = game;
    this->textureManager = textureManager;

    gameMenu = new GameMenu( json, dungeon, renderer, textureManager );
    pauseMenu = new PauseMenu( renderer, game, textureManager );
    mainMenu = new MainMenu( renderer, textureManager, game, json );

}

void UserInterface::Render()
{
    if( game->isMainMenu() )
        mainMenu->Render();
    else if( !game->Paused() )
        gameMenu->Render();
    else
        pauseMenu->Render();
}

void UserInterface::HandleEvents( SDL_Event* event )
{
    if( game->isMainMenu() )
        mainMenu->HandleEvents( event );
    else if( !game->Paused() )
        gameMenu->HandleEvents( event );
    else
        pauseMenu->HandleEvents( event );
}

void UserInterface::Reset( float multiplier )
{
    gameMenu->Reset( multiplier );
}