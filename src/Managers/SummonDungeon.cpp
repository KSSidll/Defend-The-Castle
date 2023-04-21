#include "SummonDungeon.h"
#include <unordered_map>

SummonDungeon::SummonDungeon ()
{
	renderer = nullptr;
	textureManager = nullptr;
	player = nullptr;
	objectArray = nullptr;
}

SummonDungeon::~SummonDungeon ()
{
	for (auto &summon : pendingKills)
	{
		delete summon;
	}

	delete objectArray;

	player = nullptr;
	textureManager = nullptr;
	renderer = nullptr;
}

SummonDungeon::SummonDungeon (SDL_Renderer *renderer,
                              const TextureManager *textureManager,
                              Player *player)
{
	this->renderer = renderer;
	this->textureManager = textureManager;
	this->player = player;
	this->objectArray = new std::deque<PlayerSummon> ();
}

void
SummonDungeon::KillPending ()
{
	for (const auto &summon : pendingKills)
	{
		for (int itr = objectArray->size () - 1; itr >= 0; --itr)
		{
			if (objectArray->at (itr).GetId () == summon->GetId ())
			{
				std::swap (objectArray->at (itr), objectArray->back ());
				objectArray->pop_back ();
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
	if (!pendingKills.empty ())
		KillPending ();

	for (auto &summon : *objectArray)
	{
		summon.Update ();
		if (summon.KillPending ())
			KillSummonObject (&summon);
	}
}

void
SummonDungeon::Render () const
{
	for (const auto &summon : *objectArray)
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
SummonDungeon::SummonObject (const rapidjson::Value &object)
{
	if (player->Summon (object["cost"].GetInt ()))
	{
		auto test = PlayerSummon (
			renderer, textureManager->GetTexture (object["textureSrc"]),
			object, id);
		objectArray->push_back (
			{ renderer, textureManager->GetTexture (object["textureSrc"]),
		      object, id });
		++id;
	}
}

std::deque<PlayerSummon> *
SummonDungeon::getObjectArray () const
{
	return objectArray;
};