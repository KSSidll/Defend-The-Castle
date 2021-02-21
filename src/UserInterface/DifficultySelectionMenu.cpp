#include "DifficultySelectionMenu.hpp"

DifficultySelectionMenu::DifficultySelectionMenu()
{
    this->game = nullptr;
    this->renderer = nullptr;
}

DifficultySelectionMenu::~DifficultySelectionMenu()
{
    this->renderer = nullptr;
    this->game = nullptr;
}

DifficultySelectionMenu::DifficultySelectionMenu( SDL_Renderer* renderer, Game* game, TextureManager* textureManager )
{
    this->game = game;
    this->renderer = renderer;

    background = SceneObject( textureManager->GetTexture( "darkBackground" ), renderer );
    label = UILabel( renderer, 0, 50, "assets/fonts/Sans.ttf", 48, "Select Difficulty", {255,255,255}, 1024 );

    buttons.push_back({
        new Button( textureManager->GetButtonTexture( "button1" ), easyButtonPos, renderer, []( Game* game ){ game->ChangeEnemyLevelMultiplier( 1.05 ); } ),
        UILabel( renderer, easyButtonPos.x, easyButtonPos.y, "assets/fonts/Sans.ttf", 32, "Easy", {255,255,255}, easyButtonPos.w, easyButtonPos.h )
    });

    buttons.push_back({
        new Button( textureManager->GetButtonTexture( "button1" ), mediumButtonPos, renderer, []( Game* game ){ game->ChangeEnemyLevelMultiplier( 1.1 ); } ),
        UILabel( renderer, mediumButtonPos.x, mediumButtonPos.y, "assets/fonts/Sans.ttf", 32, "Medium", {255,255,255}, mediumButtonPos.w, mediumButtonPos.h )
    });

    buttons.push_back({
        new Button( textureManager->GetButtonTexture( "button1" ), hardButtonPos, renderer, []( Game* game ){ game->ChangeEnemyLevelMultiplier( 1.15 ); } ),
        UILabel( renderer, hardButtonPos.x, hardButtonPos.y, "assets/fonts/Sans.ttf", 32, "Hard", {255,255,255}, hardButtonPos.w, hardButtonPos.h )
    });
}

void DifficultySelectionMenu::Render()
{
    background.Render();
    label.Render();
    for( auto& button : buttons )
    {
        button.button->Render();
        button.label.Render();
    }
}

void DifficultySelectionMenu::HandleEvents( SDL_Event* event )
{
    for( auto& button : buttons )
    {
        if( button.button->HandleEvents( event ) )
            button.button->game( game );
    }
}