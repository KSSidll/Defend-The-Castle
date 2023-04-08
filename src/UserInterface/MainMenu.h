#ifndef USER_INTERFACE_MAIN_MENU_H_
#define USER_INTERFACE_MAIN_MENU_H_

#include <SDL2/SDL.h>
#include <deque>

struct LabeledButton;

class Game;
class SceneObject;
class UILabel;
class TextureManager;

class MainMenu
{
    private:
        Game* game;
        SDL_Renderer* renderer;

        std::deque<LabeledButton> buttons;
        SceneObject* background;

        UILabel* mainMenuLabel;

        SDL_Rect newGameButtonPos = { 362,200,300,150 };
        SDL_Rect continueButtonPos = { 362,400,300,150 };
        SDL_Rect quitButtonPos = { 412,600,200,100 };

    public:
        MainMenu();
        ~MainMenu();

        MainMenu( SDL_Renderer* renderer, TextureManager* textureManager, Game* game );

        void Render();
        void HandleEvents( SDL_Event* event );
};

#endif // USER_INTERFACE_MAIN_MENU_H_