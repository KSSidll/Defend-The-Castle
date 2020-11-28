#include <unordered_map>
#include <iostream>
#include "Button.hpp"

Button::Button(rapidjson::Value& json, SDL_Renderer* renderer)
{
    this->renderer = renderer;

    std::unordered_map<std::string, int&> nobody_cares;
    nobody_cares.insert({ "xPos", rect.x });
    nobody_cares.insert({ "yPos", rect.y });
    nobody_cares.insert({ "width", rect.w });
    nobody_cares.insert({ "height", rect.h });

    for (auto itr = json.MemberBegin(); itr != json.MemberEnd(); ++itr)
    {
        try 
        {
            nobody_cares.at( (std::string)itr->name.GetString() ) = itr->value.GetInt();
        } 
        catch (std::out_of_range e)
        {
            std::cerr << e.what();
        }
    }
}

Button::Button(rapidjson::Value& json, SDL_Renderer* renderer, void (*callback)()) : Button(json, renderer)
{
    this->callback = callback;
}

Button::Button(rapidjson::Value& json, SDL_Renderer* renderer, void (*callback)(), rapidjson::Value& entityDoc) : Button(json, renderer)
{
    this->dungeon = dungeon;
    this->callback = callback;
    this->entityDoc = &entityDoc;
}

Button::~Button()
{
    
}

void Button::Render()
{
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderDrawRect(renderer,&rect);
    SDL_RenderFillRect(renderer, &rect);
}
