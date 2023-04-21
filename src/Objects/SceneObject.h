#ifndef OBJECTS_SCENE_OBJECT_H_
#define OBJECTS_SCENE_OBJECT_H_

#include "../Global.h"
#include <SDL2/SDL.h>

class SceneObject
{
  protected:
	SDL_Renderer *renderer;
	SDL_Texture *objTexture;
	SDL_Rect destRect;

	bool fullscreen = true;

  public:
	SceneObject ();
	virtual ~SceneObject ();

	SceneObject (SDL_Renderer *renderer, SDL_Texture *objTexture);
	SceneObject (SDL_Renderer *renderer, SDL_Texture *objTexture,
	             SDL_Rect destRect);

	void Render () const;
};

#endif // OBJECTS_SCENE_OBJECT_H_