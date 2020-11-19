#define SDL_MAIN_HANDLED

#include "SummonDungeon.hpp"

class Game
{
private:
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
    rapidjson::Document objectsDoc;
    SummonDungeon summonDungeon;
    SceneObject* background;

public:
    Game(){};
    ~Game(){};

    void init(const char* title, int width, int height, bool fullscreen);
    
    void handleEvents();
    void update();
    void render();
    void clean();

    bool running() { return isRunning; };
};