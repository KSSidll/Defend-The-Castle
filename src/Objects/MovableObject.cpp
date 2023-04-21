#include "MovableObject.h"

MovableObject::MovableObject () { originalJsonValues = nullptr; }
MovableObject::~MovableObject () { originalJsonValues = nullptr; }

void
MovableObject::Move ()
{
	destRect.x += (int)xShift * movementVector;
	xShift -= (int)xShift;
}

MovableObject::MovableObject (SDL_Renderer *renderer, SDL_Texture *objTexture,
                              const rapidjson::Value &object)
	: SceneObject (renderer, objTexture)
{
	originalJsonValues = &object;

	renderScale = object["renderScale"].GetDouble ();

	srcRect.x = object["srcRectX"].GetInt ();
	srcRect.y = object["srcRectY"].GetInt ();
	srcRect.h = object["srcRectH"].GetInt ();
	srcRect.w = object["srcRectW"].GetInt ();

	OsrcRect.x = srcRect.x;
	OsrcRect.y = srcRect.y;
	destRect.h = srcRect.h * renderScale;
	destRect.w = srcRect.w * renderScale;

	for (const auto &position : object["positions"].GetArray ())
		animationLengths.push_back (position.GetInt ());

	SetObjectValues (object);
}

void
MovableObject::SetObjectValues (const rapidjson::Value &object)
{
	destRect.x = object["destRectX"].GetInt ();
	destRect.y = object["destRectY"].GetInt ();
}

void
MovableObject::Update ()
{
	isAnimationDone = false;

	if (animationSpeed)
	{
		if (animationFramesSkipped
		    == ANIMATION_SPEED_DIVISOR / (FPS * animationSpeed))
		{
			++animationXpos;

			srcRect.x = srcRect.w * animationXpos;
			srcRect.y = srcRect.h * animationYpos;

			if (animationXpos == animationLengths[animationYpos] - 1)
			{
				animationXpos = 0;
				isAnimationDone = true;
			}

			animationFramesSkipped = 0;
		}
		else
			++animationFramesSkipped;
	}
}

void
MovableObject::Render () const
{
	SDL_RenderCopy (renderer, objTexture, &srcRect, &destRect);
}

void
MovableObject::Reset ()
{
	animationFramesSkipped = 0;
	animationYpos = 0;
	animationXpos = 0;
	animationSpeed = 5;
	xShift = 0;
	srcRect.x = srcRect.w * animationXpos;
	srcRect.y = srcRect.h * animationYpos;
	isMoving = true;
	isAnimationDone = false;
	SetObjectValues (*originalJsonValues);
}

int
MovableObject::GetPosition () const
{
	return destRect.x;
};