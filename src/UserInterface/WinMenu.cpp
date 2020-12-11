#include "WinMenu.hpp"

WinMenu::WinMenu( SDL_Renderer* renderer, Game* game, TextureManager* textureManager )
{
    this->renderer = renderer;
    this->game = game;

    background = new SceneObject( textureManager->GetTexture( "darkBackground" ), renderer );

    label = new UILabel( renderer, 0, 20, "assets/fonts/Sans.ttf", 72, "You Won", {255,255,255}, 1024 );

    UILabel* saveLabel = new UILabel( renderer, saveButtonPos.x, saveButtonPos.y, "assets/fonts/Sans.ttf", 32, "Save", {255,255,255}, saveButtonPos.w, saveButtonPos.h );
    buttons.push_back( new Button( textureManager->GetButtonTexture( "button1" ), saveLabel, saveButtonPos, renderer, []( Game* game ){  } ) );

    UILabel* shopLabel = new UILabel( renderer, shopButtonPos.x, shopButtonPos.y, "assets/fonts/Sans.ttf", 32, "Shop", {255,255,255}, shopButtonPos.w, shopButtonPos.h );
    buttons.push_back( new Button( textureManager->GetButtonTexture( "button1" ), shopLabel, shopButtonPos, renderer, []( Game* game ){  } ) );

    UILabel* nextLevelLabel = new UILabel( renderer, nextLevelButtonPos.x, nextLevelButtonPos.y, "assets/fonts/Sans.ttf", 32, "Next Level", {255,255,255}, nextLevelButtonPos.w, nextLevelButtonPos.h );
    buttons.push_back( new Button( textureManager->GetButtonTexture( "button1" ), nextLevelLabel, nextLevelButtonPos, renderer, []( Game* game ){ game->IncreaseLevel(); } ) );
}

void WinMenu::Render()
{
    background->Render();
    label->Render();
    for( const auto& button : buttons )
    {
        button->Render();
    }
}

void WinMenu::HandleEvents( SDL_Event* event )
{
    for( const auto& button : buttons )
    {
        if( button->HandleEvents( event ) )
            button->game( game );
    }
}