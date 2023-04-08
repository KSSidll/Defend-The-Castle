#ifndef OBJECTS_SCENE_OBJECT_H_
#define OBJECTS_SCENE_OBJECT_H_

#include "../Engine/Global.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class SceneObject
{
    protected:
        SDL_Texture* objTexture;
        SDL_Renderer* renderer;
        SDL_Rect position;
        bool fullScreen = true;

    public:
        SceneObject();
        ~SceneObject();

        SceneObject( SDL_Texture* objTexture, SDL_Renderer* renderer, SDL_Rect position );
        SceneObject( SDL_Texture* objTexture, SDL_Renderer* renderer );

        void Render();
};

#endif // OBJECTS_SCENE_OBJECT_H_