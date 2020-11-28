#include "UserInterface.hpp"

UserInterface::UserInterface(rapidjson::Value& json, SummonDungeon* dungeon, SDL_Renderer* renderer)
{
    this->renderer = renderer;
    this->dungeon = dungeon;
    
    for(auto& button : json["Buttons"].GetArray())
    {
        Button tmpButton(button, renderer);
        buttons.push_back(tmpButton);
    }
}

void UserInterface::Render()
{
    for(auto button : buttons)
    {
        button.Render();
    }
}