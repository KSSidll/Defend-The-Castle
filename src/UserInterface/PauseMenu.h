#ifndef USER_INTERFACE_PAUSE_MENU_H_
#define USER_INTERFACE_PAUSE_MENU_H_

#include <SDL2/SDL.h>
#include <deque>

struct LabeledButton;

class Game;
class SceneObject;
class TextureManager;
class UILabel;

class PauseMenu
{
    private:
        Game* game;
        SDL_Renderer* renderer;

        std::deque<LabeledButton> buttons;
        SceneObject* background;
        UILabel* label;

        SDL_Rect resumeButtonPos = {412,200,200,100};
        SDL_Rect exitButtonPos = {412,400,200,100};

    public:
        PauseMenu();
        ~PauseMenu();

        PauseMenu( SDL_Renderer* renderer, Game* game, TextureManager* textureManager );

        void Render();
        void HandleEvents( SDL_Event* event );
};

#endif // USER_INTERFACE_PAUSE_MENU_H_