#include "../Managers/TextureManager.hpp"
#include "../Objects/SceneObject.hpp"
#include "../Engine/Game.hpp"
#include "LoseMenu.hpp"
#include "Button.hpp"
#include "UILabel.hpp"

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

    background = new SceneObject( textureManager->GetTexture( "darkBackground" ), renderer );

    label = new UILabel( renderer, 0, 20, "assets/fonts/Sans.ttf", 72, "You Lost", {255,255,255}, 1024 );

    buttons.push_back({
        Button( textureManager->GetButtonTexture( "button1" ), exitButtonPos, renderer, []( Game* game ){ game->MainMenu(); } ),
        {{"", UILabel( renderer, exitButtonPos.x, exitButtonPos.y, "assets/fonts/Sans.ttf", 48, "Exit", {255,255,255}, exitButtonPos.w, exitButtonPos.h )}}
    });

    buttons.push_back({
        Button( textureManager->GetButtonTexture( "button1" ), loadButtonPos, renderer, []( Game* game ){ game->Load(); } ),
        {{"", UILabel( renderer, loadButtonPos.x, loadButtonPos.y, "assets/fonts/Sans.ttf", 32, "Load Previous Save", {255,255,255}, loadButtonPos.w, loadButtonPos.h )}}
    });
}

void LoseMenu::Render()
{
    background->Render();
    label->Render();
    for( auto& button : buttons )
    {
        button.Render();
    }
}

void LoseMenu::HandleEvents( SDL_Event* event )
{
    for( auto& button : buttons )
    {
        if( button.HandleEvents( event ) )
            button.button.game( game );
    }
}