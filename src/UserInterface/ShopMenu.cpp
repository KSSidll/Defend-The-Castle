#include "ShopMenu.hpp"

ShopMenu::ShopMenu( SDL_Renderer* renderer, Game* game, TextureManager* textureManager, Player* player )
{
    this->renderer = renderer;
    this->game = game;
    this->player = player;

    background = new SceneObject( textureManager->GetTexture( "darkBackground" ), renderer );
    label = new UILabel( renderer, 0, 50, "assets/fonts/Sans.ttf", 48, "Item Shop", {255,255,255}, 1024 );

    playerInfoLabel = new UILabel( renderer, label->GetPosition().x , label->GetPosition().y + label->GetPosition().h + 5, "assets/fonts/Sans.ttf", 24, "Fuko " + std::to_string( player->GetFuko() ), {255,255,255}, label->GetPosition().w );
    warriorLabel = new UILabel( renderer, 1024 / 3 * 0, 160, "assets/fonts/Sans.ttf", 24, "Warrior", {255,255,255}, 1024 / 3 );
    tankLabel = new UILabel( renderer, 1024 / 3 * 1, 160, "assets/fonts/Sans.ttf", 24, "Tank", {255,255,255}, 1024 / 3 );
    archerLabel = new UILabel( renderer, 1024 / 3 * 2, 160, "assets/fonts/Sans.ttf", 24, "Archer", {255,255,255}, 1024 / 3 );

    UILabel* backButtonLabel = new UILabel( renderer, backButtonPos.x, backButtonPos.y, "assets/fonts/Sans.ttf", 24, "Return", {255,255,255}, backButtonPos.w, backButtonPos.h );
    buttons.push_back( new Button( textureManager->GetButtonTexture( "button1" ), backButtonLabel, backButtonPos, renderer, []( Game* game ){ game->WinMenu(); } ) );

}

void ShopMenu::Update()
{
    playerInfoLabel->ChangeText( "Fuko " + std::to_string( player->GetFuko() ) );
}

void ShopMenu::Render()
{
    background->Render();
    label->Render();

    playerInfoLabel->Render();
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