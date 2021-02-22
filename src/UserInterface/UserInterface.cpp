#include "../Managers/SummonDungeon.hpp"
#include "../Managers/TextureManager.hpp"
#include "../Managers/Player.hpp"
#include "../Engine/Game.hpp"
#include "UserInterface.hpp"
#include "MainMenu.hpp"
#include "GameMenu.hpp"
#include "PauseMenu.hpp"
#include "DifficultySelectionMenu.hpp"
#include "WinMenu.hpp"
#include "LoseMenu.hpp"
#include "ShopMenu.hpp"

UserInterface::UserInterface()
{
    game = nullptr;
    gameMenu = nullptr;
    pauseMenu = nullptr;
    mainMenu = nullptr;
    difficultySelectionMenu = nullptr;
    winMenu = nullptr;
    loseMenu = nullptr;
    shopMenu = nullptr;
}

UserInterface::~UserInterface()
{
    shopMenu = nullptr;
    loseMenu = nullptr;
    winMenu = nullptr;
    difficultySelectionMenu = nullptr;
    mainMenu = nullptr;
    pauseMenu = nullptr;
    gameMenu = nullptr;
    game = nullptr;
}

UserInterface::UserInterface( rapidjson::Value* json, SummonDungeon* dungeon, SDL_Renderer* renderer, TextureManager* textureManager, Game* game, Player* player )
{
    this->game = game;

    gameMenu = new GameMenu( json, dungeon, renderer, textureManager, player, game );
    pauseMenu = new PauseMenu( renderer, game, textureManager );
    mainMenu = new MainMenu( renderer, textureManager, game );
    difficultySelectionMenu = new DifficultySelectionMenu( renderer, game, textureManager );
    winMenu = new WinMenu( renderer, game, textureManager );
    loseMenu = new LoseMenu( renderer, game, textureManager );
    shopMenu = new ShopMenu( renderer, game, textureManager, player, json );
}

void UserInterface::Update()
{
    if( game->isShopMenu() )
        shopMenu->Update();

    else if( !game->Paused() )
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

    else if( game->isShopMenu() )
        shopMenu->Render();

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

    else if( game->isShopMenu() )
        shopMenu->HandleEvents( event );
        
    else if( game->Paused() )
        pauseMenu->HandleEvents( event );

    else
        gameMenu->HandleEvents( event );
}

void UserInterface::Reset( float multiplier )
{
    gameMenu->Reset( multiplier );
}

void UserInterface::Save( rapidjson::Document* saveJson )
{
    shopMenu->Save( saveJson );
}

void UserInterface::Load( rapidjson::Value* saveJson )
{
    shopMenu->Load( saveJson );
}