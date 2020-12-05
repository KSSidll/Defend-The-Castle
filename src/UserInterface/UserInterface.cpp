#include "UserInterface.hpp"

UserInterface::UserInterface( rapidjson::Value& json, SummonDungeon* dungeon, SDL_Renderer* renderer, const bool* paused )
{
    this->paused = paused;

    gameMenu = new GameMenu( json, dungeon, renderer );

}

void UserInterface::Render()
{
    if( !*paused )
    {
        gameMenu->Render();
    }
}

void UserInterface::HandleEvents( SDL_Event* event )
{
    if( !*paused )
    {
        gameMenu->HandleEvents( event );
    }
}