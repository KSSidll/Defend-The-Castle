#include "SummonDungeon.h"

SummonDungeon::SummonDungeon ()
{
	textureManager = nullptr;
	renderer = nullptr;
	player = nullptr;
	objectArray = nullptr;
}

SummonDungeon::~SummonDungeon ()
{
	player = nullptr;
	renderer = nullptr;
	textureManager = nullptr;

	for (auto &summon : pendingKills)
	{
		delete summon;
	}

	delete objectArray;
}

SummonDungeon::SummonDungeon (const TextureManager *textureManager,
                              SDL_Renderer *renderer, Player *player)
	: SummonDungeon::SummonDungeon ()
{
	this->textureManager = textureManager;
	this->renderer = renderer;
	this->player = player;
	this->objectArray = new std::deque<PlayerSummon>;
}

void
SummonDungeon::KillPending ()
{
	for (const auto &summon : pendingKills)
	{
		for (size_t i = 0; i != objectArray->size (); ++i)
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

	for (auto &summon : pendingKills)
	{
		delete summon;
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
		auto test
			= PlayerSummon (textureManager->GetTexture (object["textureSrc"]),
		                    object, renderer, id);
		objectArray->push_back (
			{ textureManager->GetTexture (object["textureSrc"]), object,
		      renderer, id });
		++id;
	}
}

std::deque<PlayerSummon> *
SummonDungeon::getObjectArray () const
{
	return objectArray;
};