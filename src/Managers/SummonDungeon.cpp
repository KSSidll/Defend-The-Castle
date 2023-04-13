#include "SummonDungeon.h"
#include "../Objects/PlayerSummon.h"
#include "Player.h"
#include "TextureManager.h"
#include <rapidjson/document.h>

SummonDungeon::SummonDungeon ()
{
	textureManager = nullptr;
	renderer = nullptr;
	player = nullptr;
	objectArray = new std::deque<PlayerSummon>;
}

SummonDungeon::~SummonDungeon ()
{
	objectArray = nullptr;
	player = nullptr;
	renderer = nullptr;
	textureManager = nullptr;
}

SummonDungeon::SummonDungeon (TextureManager *textureManager,
                              SDL_Renderer *renderer, Player *player)
	: SummonDungeon::SummonDungeon ()
{
	this->textureManager = textureManager;
	this->renderer = renderer;
	this->player = player;
}

void
SummonDungeon::KillPending ()
{
	for (auto &summon : pendingKills)
	{
		for (int i = 0; i != objectArray->size (); ++i)
		{
			if (objectArray->at (i).GetId () == summon->GetId ())
			{
				objectArray->at (i) = objectArray->back ();
				objectArray->pop_back ();
				--i;
				break;
			}
		}
	}

	pendingKills.clear ();
}

void
SummonDungeon::KillSummonObject (PlayerSummon *summon)
{
	pendingKills.push_back (summon);
}

void
SummonDungeon::Update ()
{
	KillPending ();

	for (auto &summon : *objectArray)
	{
		summon.Update ();
		if (summon.KillPending ())
			KillSummonObject (&summon);
	}
}

void
SummonDungeon::Render ()
{
	for (auto &summon : *objectArray)
	{
		summon.Render ();
	}
}

void
SummonDungeon::Reset ()
{
	objectArray->clear ();
	pendingKills.clear ();
	id = 0;
}

void
SummonDungeon::SummonObject (rapidjson::Value &object)
{
	if (player->Summon (object["cost"].GetInt ()))
	{
		objectArray->push_back (
			{ textureManager->GetTexture (object["textureSrc"]), object,
		      renderer, id });
		++id;
	}
}

std::deque<PlayerSummon> *
SummonDungeon::getObjectArray ()
{
	return objectArray;
};