#pragma once
#include "Button.hpp"
#include <deque>

class Button;
class Game;

class WinMenu
{
    private:
        Game* game;
        std::deque<Button*> buttons;
        SDL_Renderer* renderer;
        SceneObject* background;
        UILabel* label;

        SDL_Rect saveButtonPos = {156,334,200,100};
        SDL_Rect shopButtonPos = {412,334,200,100};
        SDL_Rect nextLevelButtonPos = {668,334,200,100};
        
    public:
        WinMenu( SDL_Renderer* renderer, Game* game, TextureManager* textureManager );
        ~WinMenu(){};

        void Render();
        void HandleEvents( SDL_Event* event );
};