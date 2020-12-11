#include "UserInterface.hpp"

UserInterface::UserInterface( rapidjson::Value& json, SummonDungeon* dungeon, SDL_Renderer* renderer, TextureManager* textureManager, Game* game )
{
    this->game = game;

    gameMenu = new GameMenu( json, dungeon, renderer, textureManager );
    pauseMenu = new PauseMenu( renderer, game, textureManager );
    mainMenu = new MainMenu( renderer, textureManager, game, json );
    difficultySelectionMenu = new DifficultySelectionMenu( renderer, game, textureManager, json );

}

void UserInterface::Render()
{
    if( game->isMainMenu() )
        mainMenu->Render();
    else if( game->DifficultyChange() )
        difficultySelectionMenu->Render();
    else if( game->Paused() )
        pauseMenu->Render();
    else
        gameMenu->Render();
}

void UserInterface::HandleEvents( SDL_Event* event )
{
    if( game->isMainMenu() )
        mainMenu->HandleEvents( event );
    else if( game->DifficultyChange() )
        difficultySelectionMenu->HandleEvents( event );
    else if( game->Paused() )
        pauseMenu->HandleEvents( event );
    else
        gameMenu->HandleEvents( event );
}

void UserInterface::Reset( float multiplier )
{
    gameMenu->Reset( multiplier );
}