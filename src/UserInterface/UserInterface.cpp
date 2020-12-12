#include "UserInterface.hpp"

UserInterface::UserInterface( rapidjson::Value& json, SummonDungeon* dungeon, SDL_Renderer* renderer, TextureManager* textureManager, Game* game, Player* player )
{
    this->game = game;

    gameMenu = new GameMenu( json, dungeon, renderer, textureManager, player, game );
    pauseMenu = new PauseMenu( renderer, game, textureManager );
    mainMenu = new MainMenu( renderer, textureManager, game, json );
    difficultySelectionMenu = new DifficultySelectionMenu( renderer, game, textureManager, json );
    winMenu = new WinMenu( renderer, game, textureManager );
    loseMenu = new LoseMenu( renderer, game, textureManager );
}

void UserInterface::Update()
{
    gameMenu->Update();
}

void UserInterface::Render()
{
    if( game->isMainMenu() )
        mainMenu->Render();

    else if( game->isDifficultyMenu() )
        difficultySelectionMenu->Render();

    else if( game->isWinMenu() )
        winMenu->Render();

    else if( game->isLoseMenu() )
        loseMenu->Render();

    else if( game->Paused() )
        pauseMenu->Render();

    else
        gameMenu->Render();
}

void UserInterface::HandleEvents( SDL_Event* event )
{
    if( game->isMainMenu() )
        mainMenu->HandleEvents( event );

    else if( game->isDifficultyMenu() )
        difficultySelectionMenu->HandleEvents( event );

    else if( game->isWinMenu() )
        winMenu->HandleEvents( event );

    else if( game->isLoseMenu() )
        loseMenu->HandleEvents( event );
        
    else if( game->Paused() )
        pauseMenu->HandleEvents( event );

    else
        gameMenu->HandleEvents( event );
}

void UserInterface::Reset( float multiplier )
{
    gameMenu->Reset( multiplier );
}