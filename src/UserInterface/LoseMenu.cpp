#include "LoseMenu.hpp"

LoseMenu::LoseMenu( SDL_Renderer* renderer, Game* game, TextureManager* textureManager )
{
    this->renderer = renderer;
    this->game = game;

    background = new SceneObject( textureManager->GetTexture( "darkBackground" ), renderer );

    label = new UILabel( renderer, 0, 20, "assets/fonts/Sans.ttf", 72, "You Lost", {255,255,255}, 1024 );

    UILabel* exitButtonLabel = new UILabel( renderer, exitButtonPos.x, exitButtonPos.y, "assets/fonts/Sans.ttf", 48, "Exit", {255,255,255}, exitButtonPos.w, exitButtonPos.h );
    buttons.push_back( new Button( textureManager->GetButtonTexture( "button1" ), exitButtonLabel, exitButtonPos, renderer, []( Game* game ){ game->MainMenu(); } ) );

    UILabel* loadButtonLabel = new UILabel( renderer, loadButtonPos.x, loadButtonPos.y, "assets/fonts/Sans.ttf", 32, "Load Previous Save", {255,255,255}, loadButtonPos.w, loadButtonPos.h );
    buttons.push_back( new Button( textureManager->GetButtonTexture( "button1" ), loadButtonLabel, loadButtonPos, renderer, []( Game* game ){ game->Load(); } ) );
}

void LoseMenu::Render()
{
    background->Render();
    label->Render();
    for( const auto& button : buttons )
    {
        button->Render();
    }
}

void LoseMenu::HandleEvents( SDL_Event* event )
{
    for( const auto& button : buttons )
    {
        if( button->HandleEvents( event ) )
            button->game( game );
    }
}