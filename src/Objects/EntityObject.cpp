#include "EntityObject.h"

EntityObject::EntityObject () {}
EntityObject::~EntityObject () {}

void
EntityObject::Move ()
{
	xShift += (float)(movementSpeed) / 20;
	MovableObject::Move ();
}

EntityObject::EntityObject (SDL_Renderer *renderer, SDL_Texture *objTexture,
                            const rapidjson::Value &object)
	: MovableObject (renderer, objTexture, object)
{
	SetObjectValues (object);
}

void
EntityObject::Kill ()
{
	if (alive)
	{
		alive = false;
		attacking = false;
		isMoving = false;
		animationYpos = animationLengths.size () - 1;
		animationSpeed = 20;
		animationXpos = 0;
		animationFramesSkipped = 0;
	}
}

void
EntityObject::Attack ()
{
	if (alive && !attacking)
	{
		attacking = true;
		isMoving = false;
		animationYpos = 1;
		animationSpeed = attackSpeed;
		animationXpos = 0;
		animationFramesSkipped = 0;
	}
}

void
EntityObject::SetObjectValues (const rapidjson::Value &object,
                               float multiplier)
{
	health = object["health"].GetInt () * multiplier;
	attackDamage = object["attackDamage"].GetInt () * multiplier;
	range = object["range"].GetInt ();
	attackSpeed = object["attackSpeed"].GetInt () * multiplier;
	movementSpeed = object["movementSpeed"].GetInt () * multiplier;
	animationSpeed = movementSpeed;
}

void
EntityObject::SetObjectValues (const rapidjson::Value &object)
{
	EntityObject::SetObjectValues (object, 1);
}

void
EntityObject::Update ()
{
	if (health <= 0 && alive)
		Kill ();

	if (attacking && isAnimationDone)
	{
		attacking = false;
		isMoving = true;
		animationYpos = 0;
		animationSpeed = movementSpeed;
		srcRect.x = OsrcRect.x;
		srcRect.y = OsrcRect.y;
	}

	MovableObject::Update ();
}

void
EntityObject::Render () const
{
	if (!pendingKill)
	{
		MovableObject::Render ();
	}
}

void
EntityObject::Reset ()
{
	attacking = false;
	pendingKill = false;
	alive = true;

	MovableObject::Reset ();
	SetObjectValues (*originalJsonValues);
}

void
EntityObject::Reset (float multiplier)
{
	attacking = false;
	pendingKill = false;
	alive = true;

	MovableObject::Reset ();
	SetObjectValues (*originalJsonValues, multiplier);
}

void
EntityObject::HandleCollision ()
{
	if (!attacking)
	{
		isMoving = false;
		animationYpos = 0;
		animationSpeed = 0;
		srcRect.x = OsrcRect.x;
		srcRect.y = OsrcRect.y;
	}
}

void
EntityObject::DoDamage (int damage)
{
	health -= damage;
};

float
EntityObject::GetRange () const
{
	return range;
};

int
EntityObject::GetId () const
{
	return id;
};

int
EntityObject::GetHealth () const
{
	return health;
};

bool
EntityObject::KillPending () const
{
	return pendingKill;
};

bool
EntityObject::Alive () const
{
	return alive;
};