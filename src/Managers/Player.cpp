#include "Player.h"
#include "../Global.h"

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
Player::GetFujika () const
{
	return fujika;
};

int
Player::GetFujikaLimit () const
{
	return fujikaLimit;
};

int
Player::GetFuko () const
{
	return fuko;
};

int
Player::GetFukoLimit () const
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
Player::Save (rapidjson::Document *saveJson) const
{
	rapidjson::Value object (rapidjson::kObjectType);
	object.AddMember ("fuko", fuko, saveJson->GetAllocator ());

	saveJson->AddMember ("player", object, saveJson->GetAllocator ());
}

void
Player::Load (const rapidjson::Value *saveJson)
{
	fuko = (*saveJson)["player"]["fuko"].GetInt ();
}
