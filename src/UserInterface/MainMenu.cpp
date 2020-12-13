#include "MainMenu.hpp"

MainMenu::MainMenu( SDL_Renderer* renderer, TextureManager* textureManager, Game* game )
{
    this->renderer = renderer;
    this->game = game;

    background = new SceneObject( textureManager->GetTexture( "darkBackground" ), renderer );

    mainMenuLabel = new UILabel( renderer, 0, 20, "assets/fonts/Sans.ttf", 72, "Defend The Castle", {255,255,255}, 1024 );

    UILabel* newGameLabel = new UILabel( renderer, newGameButtonPos.x, newGameButtonPos.y, "assets/fonts/Sans.ttf", 48, "New Game", {255,255,255}, newGameButtonPos.w, newGameButtonPos.h );
    buttons.push_back( new Button( textureManager->GetButtonTexture( "button1" ), newGameLabel, newGameButtonPos, renderer, []( Game* game ){ game->NewGame(); } ) );

    UILabel* continueLabel = new UILabel( renderer, continueButtonPos.x, continueButtonPos.y, "assets/fonts/Sans.ttf", 48, "Continue", {255,255,255}, continueButtonPos.w, continueButtonPos.h );
    buttons.push_back( new Button( textureManager->GetButtonTexture( "button1" ), continueLabel, continueButtonPos, renderer, []( Game* game ){ game->Load(); } ) );

    UILabel* quitLabel = new UILabel( renderer, quitButtonPos.x, quitButtonPos.y, "assets/fonts/Sans.ttf", 32, "Quit", {255,255,255}, quitButtonPos.w, quitButtonPos.h );
    buttons.push_back( new Button( textureManager->GetButtonTexture( "button1" ), quitLabel, quitButtonPos, renderer, []( Game* game ){ game->Quit(); } ) );
}

void MainMenu::Render()
{
    background->Render();
    mainMenuLabel->Render();
    for( const auto& button : buttons )
    {
        button->Render();
    }
}

void MainMenu::HandleEvents( SDL_Event* event )
{
    for( const auto& button : buttons )
    {
        if( button->HandleEvents( event ) )
            button->game( game );
    }
}