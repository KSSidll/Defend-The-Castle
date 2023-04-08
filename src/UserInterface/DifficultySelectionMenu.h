#ifndef USER_INTERFACE_DIFFICULTY_SELECTION_MENU_H_
#define USER_INTERFACE_DIFFICULTY_SELECTION_MENU_H_

#include <SDL2/SDL.h>
#include <deque>

struct LabeledButton;

class Button;
class Game;
class SceneObject;
class UILabel;
class TextureManager;

class DifficultySelectionMenu
{
    private:
        Game* game;
        SDL_Renderer* renderer;

        std::deque<LabeledButton> buttons;
        SceneObject* background;
        UILabel* label;

        float* easy;
        float* medium;
        float* hard;

        SDL_Rect easyButtonPos = {412,200,200,100};
        SDL_Rect mediumButtonPos = {412,400,200,100};
        SDL_Rect hardButtonPos = {412,600,200,100};

    public:
        DifficultySelectionMenu();
        ~DifficultySelectionMenu();

        DifficultySelectionMenu( SDL_Renderer* renderer, Game* game, TextureManager* textureManager, rapidjson::Value* json );

        void Render();
        void HandleEvents( SDL_Event* event );
};

#endif // USER_INTERFACE_DIFFICULTY_SELECTION_MENU_H_