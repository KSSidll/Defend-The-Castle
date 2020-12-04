#include "UserInterface.hpp"

UserInterface::UserInterface( rapidjson::Value& json, SummonDungeon* dungeon, SDL_Renderer* renderer, const bool* paused )
{
    this->json = json;
    this->renderer = renderer;
    this->dungeon = dungeon;
    this->paused = paused;

    SDL_Rect aa = {0,678,200,100};
    Button* summmonButton = new Button( aa, renderer, []( SummonDungeon* dungeon, rapidjson::Value& json, SDL_Renderer* renderer ){ dungeon->SummonObject( json["summons"]["warrior"], renderer ); } );
    summonButtons.push_back( summmonButton );
}

void UserInterface::Render()
{
    if( !*paused )
    {
        for( auto button : summonButtons )
        {
            button->Render();
        }

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

        
        for( auto button : menuButtons )
        {
            button->HandleEvents( event );
        }
    }
    
}