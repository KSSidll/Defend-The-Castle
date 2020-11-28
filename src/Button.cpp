#include "Button.hpp"

Button::Button(rapidjson::Value& json, SDL_Renderer* renderer)
{
    this->renderer = renderer;

    for (rapidjson::Value::ConstMemberIterator itr = json.MemberBegin(); itr != json.MemberEnd(); ++itr)
    {
        if( itr->name.GetString() == "xPos" )
            xPos = itr->value.GetInt();

        else if( itr->name.GetString() == "yPos" )
            yPos = itr->value.GetInt();

        else if( itr->name.GetString() == "width" )
            width = itr->value.GetInt();

        else if( itr->name.GetString() == "height" )
            height = itr->value.GetInt();
    }
}

Button::~Button()
{
    
}

void Button::Render()
{

}
