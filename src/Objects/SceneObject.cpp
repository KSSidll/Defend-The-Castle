#include "SceneObject.h"

SceneObject::SceneObject ()
{
	this->objTexture = nullptr;
	this->renderer = nullptr;
}

SceneObject::~SceneObject ()
{
	this->renderer = nullptr;
	this->objTexture = nullptr;
}

SceneObject::SceneObject (SDL_Texture *objTexture, SDL_Renderer *renderer)
	: SceneObject::SceneObject ()
{
	this->renderer = renderer;
	this->objTexture = objTexture;
}

SceneObject::SceneObject (SDL_Texture *objTexture, SDL_Renderer *renderer,
                          SDL_Rect position)
	: SceneObject::SceneObject (objTexture, renderer)
{
	this->position = position;
	fullScreen = false;
}

void
SceneObject::Render ()
{
	if (fullScreen)
		SDL_RenderCopy (renderer, objTexture, NULL, NULL);
	else
		SDL_RenderCopy (renderer, objTexture, NULL, &position);
}