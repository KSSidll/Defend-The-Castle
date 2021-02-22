#include "../Managers/TextureManager.hpp"
#include "../Engine/Game.hpp"
#include "../Objects/SceneObject.hpp"
#include "PauseMenu.hpp"
#include "Button.hpp"
#include "UILabel.hpp"

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

    background = new SceneObject( textureManager->GetTexture( "darkBackground" ), renderer );
    label = new UILabel( renderer, 0, 50, "assets/fonts/Sans.ttf", 48, "Paused", {255,255,255}, 1024 );

    buttons.push_back({
        Button( textureManager->GetButtonTexture( "button1" ), resumeButtonPos, renderer, []( Game* game ){ game->UnPause(); } ),
        {{"", UILabel( renderer, resumeButtonPos.x, resumeButtonPos.y, "assets/fonts/Sans.ttf", 32, "Resume", {255,255,255}, resumeButtonPos.w, resumeButtonPos.h )}}
    });
    buttons.push_back({
        Button( textureManager->GetButtonTexture( "button1" ), exitButtonPos, renderer, []( Game* game ){ game->MainMenu(); } ),
        {{"", UILabel( renderer, exitButtonPos.x, exitButtonPos.y, "assets/fonts/Sans.ttf", 32, "Exit", {255,255,255}, exitButtonPos.w, exitButtonPos.h )}}
    });
}

void PauseMenu::Render()
{
    background->Render();
    label->Render();
    for( auto& button : buttons )
    {
        button.Render();
    }
}

void PauseMenu::HandleEvents( SDL_Event* event )
{
    for( auto& button : buttons )
    {
        if( button.HandleEvents( event ) )
            button.button.game( game );
    }
}