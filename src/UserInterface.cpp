#include "UserInterface.hpp"

UserInterface::UserInterface( rapidjson::Value& json, SummonDungeon* dungeon, SDL_Renderer* renderer )
{
    this->renderer = renderer;
    this->dungeon = dungeon;
}

void UserInterface::Render()
{
    for( auto button : summonButtons )
    {
        button->Render();
    }
}