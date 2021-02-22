#include "../Managers/TextureManager.hpp"
#include "../Objects/SceneObject.hpp"
#include "../Engine/Game.hpp"
#include "DifficultySelectionMenu.hpp"
#include "Button.hpp"
#include "UILabel.hpp"

DifficultySelectionMenu::DifficultySelectionMenu()
{
    game = nullptr;
    renderer = nullptr;
    background = nullptr;
    label = nullptr;
}

DifficultySelectionMenu::~DifficultySelectionMenu()
{
    label = nullptr;
    background = nullptr;
    renderer = nullptr;
    game = nullptr;
}

DifficultySelectionMenu::DifficultySelectionMenu( SDL_Renderer* renderer, Game* game, TextureManager* textureManager )
{
    this->game = game;
    this->renderer = renderer;

    background = new SceneObject( textureManager->GetTexture( "darkBackground" ), renderer );
    label = new UILabel( renderer, 0, 50, "assets/fonts/Sans.ttf", 48, "Select Difficulty", {255,255,255}, 1024 );

    buttons.push_back({
        Button( textureManager->GetButtonTexture( "button1" ), easyButtonPos, renderer, []( Game* game ){ game->ChangeEnemyLevelMultiplier( 1.05 ); } ),
        {{"", UILabel( renderer, easyButtonPos.x, easyButtonPos.y, "assets/fonts/Sans.ttf", 32, "Easy", {255,255,255}, easyButtonPos.w, easyButtonPos.h )}}
    });

    buttons.push_back({
        Button( textureManager->GetButtonTexture( "button1" ), mediumButtonPos, renderer, []( Game* game ){ game->ChangeEnemyLevelMultiplier( 1.1 ); } ),
        {{"", UILabel( renderer, mediumButtonPos.x, mediumButtonPos.y, "assets/fonts/Sans.ttf", 32, "Medium", {255,255,255}, mediumButtonPos.w, mediumButtonPos.h )}}
    });

    buttons.push_back({
        Button( textureManager->GetButtonTexture( "button1" ), hardButtonPos, renderer, []( Game* game ){ game->ChangeEnemyLevelMultiplier( 1.15 ); } ),
        {{"", UILabel( renderer, hardButtonPos.x, hardButtonPos.y, "assets/fonts/Sans.ttf", 32, "Hard", {255,255,255}, hardButtonPos.w, hardButtonPos.h )}}
    });
}

void DifficultySelectionMenu::Render()
{
    background->Render();
    label->Render();
    for( auto& button : buttons )
    {
        button.Render();
    }
}

void DifficultySelectionMenu::HandleEvents( SDL_Event* event )
{
    for( auto& button : buttons )
    {
        if( button.HandleEvents( event ) )
            button.button.game( game );
    }
}