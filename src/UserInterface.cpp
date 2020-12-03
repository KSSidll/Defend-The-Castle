#include "UserInterface.hpp"

UserInterface::UserInterface( rapidjson::Value& json, SummonDungeon* dungeon, SDL_Renderer* renderer, const bool* paused )
{
    this->renderer = renderer;
    this->dungeon = dungeon;
    this->paused = paused;

    SDL_Rect a = {0,678,200,100};
    SummonButton* button = new SummonButton(a, renderer, dungeon, &json["summons"]["warrior"]);
    buttons.push_back( button );
}

void UserInterface::Render()
{
    if( !*paused )
    {
        for( auto button : buttons )
        {
            button->Render();
        }
    }
}

void UserInterface::HandleEvents( SDL_Event* event )
{
    if( !*paused )
    {
        for( auto button : buttons )
        {
            button->HandleEvents( event );
        }
    }
    
}