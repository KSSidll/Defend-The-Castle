#include "MainMenu.hpp"

MainMenu::MainMenu()
{
    this->game = nullptr;
    this->renderer = nullptr;
}

MainMenu::~MainMenu()
{
    this->renderer = nullptr;
    this->game = nullptr;
}

MainMenu::MainMenu( SDL_Renderer* renderer, TextureManager* textureManager, Game* game )
{
    this->game = game;
    this->renderer = renderer;

    background = SceneObject( textureManager->GetTexture( "darkBackground" ), renderer );

    mainMenuLabel = UILabel( renderer, 0, 20, "assets/fonts/Sans.ttf", 72, "Defend The Castle", {255,255,255}, 1024 );

    buttons.push_back({
        UILabel( renderer, newGameButtonPos.x, newGameButtonPos.y, "assets/fonts/Sans.ttf", 48, "New Game", {255,255,255}, newGameButtonPos.w, newGameButtonPos.h ),
        new Button( textureManager->GetButtonTexture( "button1" ), newGameButtonPos, renderer, []( Game* game ){ game->NewGame(); } ) 
    });
    buttons.push_back({
        UILabel( renderer, continueButtonPos.x, continueButtonPos.y, "assets/fonts/Sans.ttf", 48, "Continue", {255,255,255}, continueButtonPos.w, continueButtonPos.h ),
        new Button( textureManager->GetButtonTexture( "button1" ), continueButtonPos, renderer, []( Game* game ){ game->Load(); } ) 
    });
    buttons.push_back({
        UILabel( renderer, quitButtonPos.x, quitButtonPos.y, "assets/fonts/Sans.ttf", 32, "Quit", {255,255,255}, quitButtonPos.w, quitButtonPos.h ),
        new Button( textureManager->GetButtonTexture( "button1" ), quitButtonPos, renderer, []( Game* game ){ game->Quit(); } ) 
    });
}

void MainMenu::Render()
{
    background.Render();
    mainMenuLabel.Render();
    for( auto& button : buttons )
    {
        button.button->Render();
        button.label.Render();
    }
}

void MainMenu::HandleEvents( SDL_Event* event )
{
    for( auto& button : buttons )
    {
        if( button.button->HandleEvents( event ) )
            button.button->game( game );
    }
}