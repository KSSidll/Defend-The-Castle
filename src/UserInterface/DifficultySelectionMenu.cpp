#include "DifficultySelectionMenu.hpp"

DifficultySelectionMenu::DifficultySelectionMenu( SDL_Renderer* renderer, Game* game, TextureManager* textureManager )
{
    this->renderer = renderer;
    this->game = game;

    background = new SceneObject( textureManager->GetTexture( "darkBackground" ), renderer );
    label = new UILabel( renderer, 0, 50, "assets/fonts/Sans.ttf", 48, "Select Difficulty", {255,255,255}, 1024 );

    UILabel* easyLabel = new UILabel( renderer, easyButtonPos.x, easyButtonPos.y, "assets/fonts/Sans.ttf", 32, "Easy", {255,255,255}, easyButtonPos.w, easyButtonPos.h );
    buttons.push_back( new Button( textureManager->GetButtonTexture( "button1" ), easyLabel, easyButtonPos, renderer, []( Game* game ){ game->ChangeEnemyLevelMultiplier( 1.05 ); } ) );

    UILabel* mediumLabel = new UILabel( renderer, mediumButtonPos.x, mediumButtonPos.y, "assets/fonts/Sans.ttf", 32, "Medium", {255,255,255}, mediumButtonPos.w, mediumButtonPos.h );
    buttons.push_back( new Button( textureManager->GetButtonTexture( "button1" ), mediumLabel, mediumButtonPos, renderer, []( Game* game ){ game->ChangeEnemyLevelMultiplier( 1.1 ); } ) );

    UILabel* hardLabel = new UILabel( renderer, hardButtonPos.x, hardButtonPos.y, "assets/fonts/Sans.ttf", 32, "Hard", {255,255,255}, hardButtonPos.w, hardButtonPos.h );
    buttons.push_back( new Button( textureManager->GetButtonTexture( "button1" ), hardLabel, hardButtonPos, renderer, []( Game* game ){ game->ChangeEnemyLevelMultiplier( 1.15 ); } ) );

}

void DifficultySelectionMenu::Render()
{
    background->Render();
    label->Render();
    for( const auto& button : buttons )
    {
        button->Render();
    }
}

void DifficultySelectionMenu::HandleEvents( SDL_Event* event )
{
    for( const auto& button : buttons )
    {
        if( button->HandleEvents( event ) )
            button->game( game );
    }
}