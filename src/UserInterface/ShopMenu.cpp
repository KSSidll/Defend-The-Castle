#include "ShopMenu.hpp"

ShopMenu::ShopMenu( SDL_Renderer* renderer, Game* game, TextureManager* textureManager )
{
    this->renderer = renderer;
    this->game = game;

    background = new SceneObject( textureManager->GetTexture( "darkBackground" ), renderer );
    label = new UILabel( renderer, 0, 50, "assets/fonts/Sans.ttf", 48, "Item Shop", {255,255,255}, 1024 );

    warriorLabel = new UILabel( renderer, 1024 / 3 * 0, 150, "assets/fonts/Sans.ttf", 24, "Warrior", {255,255,255}, 1024 / 3 );
    tankLabel = new UILabel( renderer, 1024 / 3 * 1, 150, "assets/fonts/Sans.ttf", 24, "Tank", {255,255,255}, 1024 / 3 );
    archerLabel = new UILabel( renderer, 1024 / 3 * 2, 150, "assets/fonts/Sans.ttf", 24, "Archer", {255,255,255}, 1024 / 3 );

    UILabel* backButtonLabel = new UILabel( renderer, backButtonPos.x, backButtonPos.y, "assets/fonts/Sans.ttf", 24, "Return", {255,255,255}, backButtonPos.w, backButtonPos.h );
    buttons.push_back( new Button( textureManager->GetButtonTexture( "button1" ), backButtonLabel, backButtonPos, renderer, []( Game* game ){ game->WinMenu(); } ) );

}

void ShopMenu::Render()
{
    background->Render();
    label->Render();

    warriorLabel->Render();
    tankLabel->Render();
    archerLabel->Render();

    for( const auto& button : buttons )
    {
        button->Render();
    }
}

void ShopMenu::HandleEvents( SDL_Event* event )
{
    for( const auto& button : buttons )
    {
        if( button->HandleEvents( event ) )
            button->game( game );
    }
}