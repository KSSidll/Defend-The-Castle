#include "Player.h"
#include "../Global.h"
#include <rapidjson/document.h>

bool
Player::Summon (int cost)
{
	if (cost > fujika)
		return false;
	else
	{
		fujika -= cost;
		return true;
	}
}

bool
Player::Buy (int cost)
{
	if (cost > fuko)
		return false;
	else
	{
		fuko -= cost;
		return true;
	}
}

int
Player::GetFujika ()
{
	return fujika;
};

int
Player::GetFujikaLimit ()
{
	return fujikaLimit;
};

int
Player::GetFuko ()
{
	return fuko;
};

int
Player::GetFukoLimit ()
{
	return fukoLimit;
};

void
Player::ReturnFuko (int value)
{
	fuko += value;
};

void
Player::Update ()
{
	if (frameCounter == FPS)
	{
		if (fujika != fujikaLimit)
		{
			if (fujika + fujikaGain > fujikaLimit)
				fujika = fujikaLimit;
			else
				fujika += fujikaGain;
		}
		else if (fuko != fukoLimit)
		{
			if (fuko + fukoGain > fukoLimit)
				fuko = fukoLimit;
			else
				fuko += fukoGain;
		}

		frameCounter = 0;
	}
	else
		++frameCounter;
}

void
Player::Reset ()
{
	fujika = 0;
	frameCounter = 0;
}

void
Player::HardReset ()
{
	fujika = 0;
	fuko = 0;
	frameCounter = 0;
}

void
Player::Save (rapidjson::Document *saveJson)
{
	rapidjson::Value object (rapidjson::kObjectType);
	object.AddMember ("fuko", fuko, saveJson->GetAllocator ());

	saveJson->AddMember ("player", object, saveJson->GetAllocator ());
}

void
Player::Load (rapidjson::Value *saveJson)
{
	fuko = (*saveJson)["player"]["fuko"].GetInt ();
}
