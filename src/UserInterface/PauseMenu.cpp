#include "PauseMenu.hpp"

PauseMenu::PauseMenu( SDL_Renderer* renderer, Game* game, TextureManager* textureManager )
{
    this->renderer = renderer;
    this->textureManager = textureManager;
    this->game = game;

    background = new SceneObject( textureManager->GetTexture( "darkBackground" ), renderer );
    label = new UILabel( renderer, 0, 50, "assets/fonts/Sans.ttf", 48, "Paused", {255,255,255}, 1024 );

    UILabel* resumeLabel = new UILabel( renderer, resumeButtonPos.x, resumeButtonPos.y, "assets/fonts/Sans.ttf", 32, "Resume", {255,255,255}, resumeButtonPos.w, resumeButtonPos.h );
    buttons.push_back( new Button( textureManager->GetButtonTexture( "button1" ), resumeLabel, resumeButtonPos, renderer, []( Game* game ){ game->UnPause(); } ) );

    UILabel* quitLabel = new UILabel( renderer, quitButtonPos.x, quitButtonPos.y, "assets/fonts/Sans.ttf", 32, "Quit", {255,255,255}, quitButtonPos.w, quitButtonPos.h );
    buttons.push_back( new Button( textureManager->GetButtonTexture( "button1" ), quitLabel, quitButtonPos, renderer, []( Game* game ){ game->Quit(); } ) );
}

void PauseMenu::Render()
{
    background->Render();
    label->Render();
    for( auto& button : buttons )
    {
        button->Render();
    }
}

void PauseMenu::HandleEvents( SDL_Event* event )
{
    for( auto button : buttons )
    {
        if( button->HandleEvents( event ) )
            button->game( game );
    }
}