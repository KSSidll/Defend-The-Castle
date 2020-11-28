#include "UserInterface.hpp"

UserInterface::UserInterface(rapidjson::Value& json, SummonDungeon* dungeon, SDL_Renderer* renderer)
{
    this->renderer = renderer;
    this->dungeon = dungeon;
    
    /*
    Button *tmpButton;
    for(auto& button : json["Buttons"].GetArray())
    {
        tmpButton = new Button(button, renderer);
        buttons.push_back(tmpButton);
    }
    delete tmpButton;
    */
}

void UserInterface::Render()
{

}