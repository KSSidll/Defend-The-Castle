#ifndef OBJECTS_MOVABLE_OBJECT_H_
#define OBJECTS_MOVABLE_OBJECT_H_

#include "SceneObject.h"
#include <rapidjson/document.h>
#include <vector>

class MovableObject : public SceneObject
{
  protected:
	const rapidjson::Value *originalJsonValues;

	int movementVector = 1;
	int xpos;
	int ypos;
	int animationFramesSkipped = 0;
	int animationYpos = 0;
	int animationXpos = 0;
	int animationSpeed = 5;

	float renderScale;
	float xShift = 0;

	bool isMoving = true;
	bool isAnimationDone = false;

	SDL_Rect srcRect, destRect;
	SDL_Rect OsrcRect;
	std::vector<int> animationLengths;

	void Move ();

  public:
	MovableObject ();
	~MovableObject ();

	MovableObject (SDL_Texture *objTexture, const rapidjson::Value &object,
	               SDL_Renderer *renderer);

	void SetObjectValues (const rapidjson::Value &object);
	void Update ();
	void Render () const;
	void Reset ();
	int GetPosition () const;
};

#endif // OBJECTS_MOVABLE_OBJECT_H_