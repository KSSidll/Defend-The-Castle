#include "SceneObject.h"

SceneObject::SceneObject ()
{
	this->renderer = nullptr;
	this->objTexture = nullptr;
}

SceneObject::~SceneObject ()
{
	this->objTexture = nullptr;
	this->renderer = nullptr;
}

SceneObject::SceneObject (SDL_Renderer *renderer, SDL_Texture *objTexture)
	: renderer (renderer), objTexture (objTexture)
{
}

SceneObject::SceneObject (SDL_Renderer *renderer, SDL_Texture *objTexture,
                          SDL_Rect destRect)
	: SceneObject::SceneObject (renderer, objTexture)
{
	this->destRect = destRect;
	fullscreen = false;
}

void
SceneObject::Render () const
{
	if (fullscreen)
		SDL_RenderCopy (renderer, objTexture, NULL, NULL);
	else
		SDL_RenderCopy (renderer, objTexture, NULL, &destRect);
}