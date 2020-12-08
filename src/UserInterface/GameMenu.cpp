#include "GameMenu.hpp"

GameMenu::GameMenu( rapidjson::Value& json, SummonDungeon* dungeon, SDL_Renderer* renderer, TextureManager* textureManager )
{
    this->json = json;
    this->dungeon = dungeon;
    this->renderer = renderer;

    summonButtons.push_back( new Button( textureManager->GetTexture( "button2" ), textureManager->CreateTextTexture( "test", 72, {255,255,255} ), {0,678,200,100}, renderer, []( SummonDungeon* dungeon, rapidjson::Value& json, SDL_Renderer* renderer ){ dungeon->SummonObject( json["summons"]["warrior"], renderer ); } ) );
}

void GameMenu::Render()
{
    for( auto button : summonButtons )
    {
        button->Render();
    }
}

void GameMenu::HandleEvents( SDL_Event* event )
{
    for( auto button : summonButtons )
    {
        if( button->HandleEvents( event ) )
            button->callback( dungeon, json, renderer );
    }
}