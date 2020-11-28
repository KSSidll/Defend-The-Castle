#pragma once
#include "SummonDungeon.hpp"

class UserInterface
{
private:
    SDL_Renderer* renderer;
    
public:
    UserInterface(SummonDungeon* dungeon, SDL_Renderer* renderer);
    ~UserInterface();

    void Render();
    void HandleEvents(SDL_Event event);
};