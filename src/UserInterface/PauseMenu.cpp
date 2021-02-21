#include "PauseMenu.hpp"

PauseMenu::PauseMenu()
{
    this->game = nullptr;
    this->renderer = nullptr;
}

PauseMenu::~PauseMenu()
{
    this->renderer = nullptr;
    this->game = nullptr;
}

PauseMenu::PauseMenu( SDL_Renderer* renderer, Game* game, TextureManager* textureManager )
{
    this->game = game;
    this->renderer = renderer;

    background = SceneObject( textureManager->GetTexture( "darkBackground" ), renderer );
    label = UILabel( renderer, 0, 50, "assets/fonts/Sans.ttf", 48, "Paused", {255,255,255}, 1024 );

    buttons.push_back({
        UILabel( renderer, resumeButtonPos.x, resumeButtonPos.y, "assets/fonts/Sans.ttf", 32, "Resume", {255,255,255}, resumeButtonPos.w, resumeButtonPos.h ),
        new Button( textureManager->GetButtonTexture( "button1" ), resumeButtonPos, renderer, []( Game* game ){ game->UnPause(); } ) 
    });
    buttons.push_back({
        UILabel( renderer, exitButtonPos.x, exitButtonPos.y, "assets/fonts/Sans.ttf", 32, "Exit", {255,255,255}, exitButtonPos.w, exitButtonPos.h ),
        new Button( textureManager->GetButtonTexture( "button1" ), exitButtonPos, renderer, []( Game* game ){ game->MainMenu(); } ) 
    });
}

void PauseMenu::Render()
{
    background.Render();
    label.Render();
    for( auto& button : buttons )
    {
        button.button->Render();
        button.label.Render();
    }
}

void PauseMenu::HandleEvents( SDL_Event* event )
{
    for( auto& button : buttons )
    {
        if( button.button->HandleEvents( event ) )
            button.button->game( game );
    }
}