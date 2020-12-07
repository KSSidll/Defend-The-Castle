#include "UserInterface.hpp"

UserInterface::UserInterface( rapidjson::Value& json, SummonDungeon* dungeon, SDL_Renderer* renderer, TextureManager* textureManager, const bool* paused )
{
    this->paused = paused;
    this->textureManager = textureManager;

    gameMenu = new GameMenu( json, dungeon, renderer, textureManager );

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