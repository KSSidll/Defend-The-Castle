#include "UserInterface.hpp"

UserInterface::UserInterface( rapidjson::Value& json, SummonDungeon* dungeon, SDL_Renderer* renderer )
{
    this->renderer = renderer;
    this->dungeon = dungeon;

    SDL_Rect a = {0,678,200,100};
    SummonButton* button = new SummonButton(a, renderer, dungeon, &json["summons"]["warrior"]);
    buttons.push_back( button );
}

void UserInterface::Render()
{
    for( auto button : buttons )
    {
        button->Render();
    }
}

void UserInterface::HandleEvents( SDL_Event* event )
{
    for( auto button : buttons )
    {
        button->HandleEvents( event );
    }
}