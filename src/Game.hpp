#define SDL_MAIN_HANDLED

#include "ObjectDungeon.hpp"

class Game
{
private:
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
    rapidjson::Document objectsDoc;
    ObjectDungeon objectDungeon;
    SDL_Texture *background;

public:
    Game();
    ~Game();

    void init(const char* title, int width, int height, bool fullscreen);
    
    void handleEvents();
    void update();
    void render();
    void clean();

    bool running() { return isRunning; };
};