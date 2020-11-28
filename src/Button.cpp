#include "Button.hpp"

Button::Button(rapidjson::Value& json, SDL_Renderer* renderer)
{
    this->renderer = renderer;

    int ca;
    std::string caa;

    for (auto itr = json.MemberBegin(); itr != json.MemberEnd(); ++itr)
    {

        if( (std::string)itr->name.GetString() == "xPos" )
            rect.x = itr->value.GetInt();

        else if( (std::string)itr->name.GetString() == "yPos" )
            rect.y = itr->value.GetInt();

        else if( (std::string)itr->name.GetString() == "width" )
            rect.w = itr->value.GetInt();

        else if( (std::string)itr->name.GetString() == "height" )
            rect.h = itr->value.GetInt();
    }
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
