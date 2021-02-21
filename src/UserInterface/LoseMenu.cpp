#include "LoseMenu.hpp"

LoseMenu::LoseMenu()
{
    this->game = nullptr;
    this->renderer = nullptr;
}

LoseMenu::~LoseMenu()
{
    this->renderer = nullptr;
    this->game = nullptr;
}

LoseMenu::LoseMenu( SDL_Renderer* renderer, Game* game, TextureManager* textureManager )
{
    this->game = game;
    this->renderer = renderer;

    background = SceneObject( textureManager->GetTexture( "darkBackground" ), renderer );

    label = UILabel( renderer, 0, 20, "assets/fonts/Sans.ttf", 72, "You Lost", {255,255,255}, 1024 );

    buttons.push_back({
        UILabel( renderer, exitButtonPos.x, exitButtonPos.y, "assets/fonts/Sans.ttf", 48, "Exit", {255,255,255}, exitButtonPos.w, exitButtonPos.h ),
        new Button( textureManager->GetButtonTexture( "button1" ), exitButtonPos, renderer, []( Game* game ){ game->MainMenu(); } )
    });

    buttons.push_back({
        UILabel( renderer, loadButtonPos.x, loadButtonPos.y, "assets/fonts/Sans.ttf", 32, "Load Previous Save", {255,255,255}, loadButtonPos.w, loadButtonPos.h ),
        new Button( textureManager->GetButtonTexture( "button1" ), loadButtonPos, renderer, []( Game* game ){ game->Load(); } )
    });
}

void LoseMenu::Render()
{
    background.Render();
    label.Render();
    for( auto& button : buttons )
    {
        button.button->Render();
        button.label.Render();
    }
}

void LoseMenu::HandleEvents( SDL_Event* event )
{
    for( auto& button : buttons )
    {
        if( button.button->HandleEvents( event ) )
            button.button->game( game );
    }
}