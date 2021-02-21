#include "WinMenu.hpp"

WinMenu::WinMenu()
{
    game = nullptr;
    renderer = nullptr;
}

WinMenu::~WinMenu()
{
    renderer = nullptr;
    game = nullptr;
}
    
WinMenu::WinMenu( SDL_Renderer* renderer, Game* game, TextureManager* textureManager )
{
    this->game = game;
    this->renderer = renderer;

    background = SceneObject( textureManager->GetTexture( "darkBackground" ), renderer );

    label = UILabel( renderer, 0, 20, "assets/fonts/Sans.ttf", 72, "Level Cleared", {255,255,255}, 1024 );

    buttons.push_back({
        Button( textureManager->GetButtonTexture( "button1" ), saveButtonPos, renderer, []( Game* game ){ game->Save(true); } ),
        {{"", UILabel( renderer, saveButtonPos.x, saveButtonPos.y, "assets/fonts/Sans.ttf", 32, "Save", {255,255,255}, saveButtonPos.w, saveButtonPos.h )}}
    });

    buttons.push_back({
        Button( textureManager->GetButtonTexture( "button1" ), shopButtonPos, renderer, []( Game* game ){ game->ShopMenu(); } ),
        {{"", UILabel( renderer, shopButtonPos.x, shopButtonPos.y, "assets/fonts/Sans.ttf", 32, "Shop", {255,255,255}, shopButtonPos.w, shopButtonPos.h )}}
    });

    buttons.push_back({
        Button( textureManager->GetButtonTexture( "button1" ), nextLevelButtonPos, renderer, []( Game* game ){ game->IncreaseLevel(); } ),
        {{"", UILabel( renderer, nextLevelButtonPos.x, nextLevelButtonPos.y, "assets/fonts/Sans.ttf", 32, "Next Level", {255,255,255}, nextLevelButtonPos.w, nextLevelButtonPos.h )}}
    });
}

void WinMenu::Render()
{
    background.Render();
    label.Render();
    for( auto& button : buttons )
    {
        button.Render();
    }
}

void WinMenu::HandleEvents( SDL_Event* event )
{
    for( auto& button : buttons )
    {
        if( button.HandleEvents( event ) )
            button.button.game( game );
    }
}