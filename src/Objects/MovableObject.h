#ifndef OBJECTS_MOVABLE_OBJECT_H_
#define OBJECTS_MOVABLE_OBJECT_H_

#include "SceneObject.h"
#include <rapidjson/document.h>
#include <stdint.h>
#include <vector>

class MovableObject : public SceneObject
{
  protected:
	const rapidjson::Value *originalJsonValues;

	int movementVector = 1;
	int xpos;
	int ypos;
	int animationFramesSkipped = 0;
	unsigned int animationYpos = 0;
	unsigned int animationXpos = 0;
	int animationSpeed = 5;

	double renderScale;
	double xShift = 0;

	bool isMoving = true;
	bool isAnimationDone = false;

	SDL_Rect srcRect;
	SDL_Rect OsrcRect;
	std::vector<unsigned int> animationLengths;

  public:
	MovableObject ();
	~MovableObject ();

	MovableObject (SDL_Renderer *renderer, SDL_Texture *objTexture,
	               const rapidjson::Value &object);

	void Move ();
	void SetObjectValues (const rapidjson::Value &object);
	void Update ();
	void Render () const;
	void Reset ();
	int GetPosition () const;
};

#endif // OBJECTS_MOVABLE_OBJECT_H_