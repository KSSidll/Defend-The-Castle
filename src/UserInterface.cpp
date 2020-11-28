#include "UserInterface.hpp"

UserInterface::UserInterface(rapidjson::Value& json, SummonDungeon* dungeon, SDL_Renderer* renderer)
{
    this->renderer = renderer;
    this->dungeon = dungeon;
    for(auto& button : json["UserInterface"]["Buttons"].GetArray())
    {
        for (auto itr = button.MemberBegin(); itr != button.MemberEnd(); ++itr)
        {
            if( (std::string)itr->name.GetString() == "Usage" )
            {
                if( (std::string)itr->value.GetString() == "summon warrior")
                    //buttons.push_back( Button(button, renderer,[dungeon](){ dungeon->SummonObject(); }, json["summons"]["warrior"]) );
                break;
            }
        }
    }
}

void UserInterface::Render()
{
    for(auto button : buttons)
    {
        button.Render();
    }
}