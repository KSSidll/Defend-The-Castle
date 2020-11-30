#include "UserInterface.hpp"

UserInterface::UserInterface(rapidjson::Value& json, SummonDungeon* dungeon, SDL_Renderer* rendererm, TextureManager* textureManager)
{
    this->renderer = renderer;
    this->dungeon = dungeon;
    this->textureManager = textureManager;

    

}

void UserInterface::Render()
{
    for(auto button : buttons)
    {
        button.Render();
    }
}