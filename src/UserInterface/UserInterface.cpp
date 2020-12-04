#include "UserInterface.hpp"

UserInterface::UserInterface( rapidjson::Value& json, SummonDungeon* dungeon, SDL_Renderer* renderer, const bool* paused )
{
    this->json = json;
    this->renderer = renderer;
    this->dungeon = dungeon;
    this->paused = paused;

    SDL_Rect ButtonCoords = {0,678,200,100};
    summonButtons.push_back( new Button( ButtonCoords, renderer, []( SummonDungeon* dungeon, rapidjson::Value& json, SDL_Renderer* renderer ){ dungeon->SummonObject( json["summons"]["warrior"], renderer ); } ) );

    ButtonCoords = {0,0,300,300};
    menuButtons.push_back( new Button( ButtonCoords, renderer ) );
}

void UserInterface::Render()
{
    if( !*paused )
    {
        for( auto button : summonButtons )
        {
            button->Render();
        }
    }
    else
    {
        for( auto button : menuButtons )
        {
            button->Render();
        }
    }
    
}

void UserInterface::HandleEvents( SDL_Event* event )
{
    if( !*paused )
    {
        for( auto button : summonButtons )
        {
            bool summon = button->HandleEvents( event );
            if( summon )
                button->callback( dungeon, json, renderer );
        }
    }
    else
    {
        for( auto button : menuButtons )
        {
            button->HandleEvents( event );
        }
    }
    
    
    
}