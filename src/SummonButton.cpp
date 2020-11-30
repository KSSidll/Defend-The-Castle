#include "SummonButton.hpp"

SummonButton::SummonButton( SDL_Rect rect, SDL_Renderer* renderer, SummonDungeon* dungeon, rapidjson::Value* entityDoc )
{   
    this->rect.x = rect.x;
    this->rect.y = rect.y;
    this->rect.w = rect.w;
    this->rect.h = rect.h;

    this->renderer = renderer;

    this->dungeon = dungeon;
    this->entityDoc = entityDoc;
}

void SummonButton::Render()
{
    SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0x00 );
    SDL_RenderDrawRect( renderer,&rect );
    SDL_RenderFillRect( renderer, &rect );
}
