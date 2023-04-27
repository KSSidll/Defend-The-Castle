#include "Game.h"
#include "Managers/Player.h"
#include "Managers/SummonDungeon.h"
#include "Managers/TextureManager.h"
#include "Objects/Enemy.h"
#include "Objects/PlayerSummon.h"
#include "UserInterface/UserInterface.h"
#include <cmath>
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/writer.h>
#include <stdio.h>

Game::Game ()
{
	window = nullptr;
	renderer = nullptr;
	objectsDoc = nullptr;
	saveDoc = nullptr;
	summonDungeon = nullptr;
	textureManager = nullptr;
	userInterface = nullptr;
	player = nullptr;
	enemy = nullptr;
}

Game::~Game ()
{
	if (enemy)
		delete enemy;
	if (player)
		delete player;
	if (userInterface)
		delete userInterface;
	if (textureManager)
		delete textureManager;
	if (summonDungeon)
		delete summonDungeon;
	if (saveDoc)
		delete saveDoc;
	if (objectsDoc)
		delete objectsDoc;
	if (renderer)
		SDL_DestroyRenderer (renderer);
	if (window)
		SDL_DestroyWindow (window);
}

void
Game::Init (const char *title, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;

	objectsDoc = new rapidjson::Document ();

	FILE *objectsJsonFile = nullptr;
	fopen_s (&objectsJsonFile, "assets/objects.json", "r");

	char *readBuffer = new char[65536];
	rapidjson::FileReadStream objectsJson (objectsJsonFile, readBuffer,
	                                       sizeof (readBuffer));
	objectsDoc->ParseStream (objectsJson);
	delete[] readBuffer;
	fclose (objectsJsonFile);

	saveDoc = new rapidjson::Document ();

	if (!SDL_Init (SDL_INIT_EVERYTHING))
	{
		window
			= SDL_CreateWindow (title, SDL_WINDOWPOS_CENTERED,
		                        SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer (window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor (renderer, 50, 50, 50, 255);
		}
		isRunning = true;
	}
	else
	{
		isRunning = false;
	}

	player = new Player ();
	textureManager = new TextureManager (renderer);

	for (const auto &texture : (*objectsDoc)["textures"].GetArray ())
		textureManager->LoadTexture (texture);

	textureManager->LoadTexture ("enemyLabelBackground",
	                             "assets/prototypes/button2.png");

	textureManager->LoadButtonTexture ("button1",
	                                   "assets/prototypes/button1.png",
	                                   "assets/prototypes/button1-over.png",
	                                   "assets/prototypes/button1-down.png");
	textureManager->LoadButtonTexture ("button2",
	                                   "assets/prototypes/button2.png",
	                                   "assets/prototypes/button2-over.png",
	                                   "assets/prototypes/button2-down.png");
	textureManager->LoadButtonTexture (
		"button-arrow-up", "assets/prototypes/arrow-up.png",
		"assets/prototypes/arrow-up.png", "assets/prototypes/arrow-up.png");
	textureManager->LoadButtonTexture ("button-arrow-down",
	                                   "assets/prototypes/arrow-down.png",
	                                   "assets/prototypes/arrow-down.png",
	                                   "assets/prototypes/arrow-down.png");
	textureManager->LoadButtonTexture ("button-arrow-left",
	                                   "assets/prototypes/arrow-left.png",
	                                   "assets/prototypes/arrow-left.png",
	                                   "assets/prototypes/arrow-left.png");
	textureManager->LoadButtonTexture ("button-arrow-right",
	                                   "assets/prototypes/arrow-right.png",
	                                   "assets/prototypes/arrow-right.png",
	                                   "assets/prototypes/arrow-right.png");

	background = SceneObject (renderer,
	                          textureManager->GetTexture (
								  (*objectsDoc)["background"]["textureSrc"]));

	summonDungeon = new SummonDungeon (renderer, textureManager, player);

	enemy = new Enemy (
		renderer,
		textureManager->GetTexture ((*objectsDoc)["enemy"]["textureSrc"]),
		(*objectsDoc)["enemy"]);

	userInterface = new UserInterface (renderer, textureManager, this,
	                                   summonDungeon, player, objectsDoc);

	userInterface->EnableMainMenu ();
	Pause ();
}

void
Game::HandleEvents ()
{
	SDL_Event event;
	SDL_PollEvent (&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;

	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			if (isPaused)
			{
				userInterface->DisablePauseMenu ();
				UnPause ();
			}
			else
			{
				userInterface->EnablePauseMenu ();
				Pause ();
			}
			break;
		}
		break;
	}

	userInterface->HandleEvents (&event);
}

void
Game::Update ()
{
	userInterface->Update ();

	if (!isPaused)
	{
		HandleCollisions ();

		player->Update ();
		summonDungeon->Update ();
		enemy->Update ();
	}

	if (enemy->IsKillPending ())
		WinGame ();

	if (enemy->GetPosition () <= -250)
		LoseGame ();
}

void
Game::Render ()
{
	SDL_RenderClear (renderer);
	background.Render ();

	summonDungeon->Render ();
	enemy->Render ();

	userInterface->Render ();
	SDL_RenderPresent (renderer);
}

void
Game::Clean ()
{
	SDL_DestroyWindow (window);
	SDL_DestroyRenderer (renderer);
	SDL_Quit ();
}

void
Game::HandleCollisions ()
{
	bool bEnemyCollision = false;
	if (enemy->IsAlive ())
		for (auto &summon : *(summonDungeon->GetObjectArray ()))
		{
			if (summon.GetPosition () + summon.GetRange ()
			    > enemy->GetPosition ())
			{
				summon.HandleCollision (enemy);
			}

			if (enemy->GetPosition () < summon.GetPosition ())
			{
				bEnemyCollision = true;
			}
		}

	if (bEnemyCollision)
		for (auto &summon : *(summonDungeon->GetObjectArray ()))
		{
			if (enemy->GetPosition () - enemy->GetRange ()
			    < summon.GetPosition ())
			{
				enemy->HandleCollision (&summon);
			}
		}
}

void
Game::HardReset ()
{
	level = 0;
	player->HardReset ();
	userInterface->HardReset ();
}

void
Game::Reset ()
{
	enemy->Reset (powf (enemyStatsLevelMultiplier, level));
	summonDungeon->Reset ();
	userInterface->Reset (powf (enemyStatsLevelMultiplier, level));
	player->Reset ();
}

void
Game::Save (bool incrementLevel)
{
	FILE *saveFile = nullptr;
	fopen_s (&saveFile, "assets/save.json", "w");

	char writeBuffer[65536];
	rapidjson::FileWriteStream saveStream (saveFile, writeBuffer,
	                                       sizeof (writeBuffer));
	saveDoc->SetObject ();

	rapidjson::Value object (rapidjson::kObjectType);
	object.AddMember ("enemyStatsLevelMultiplier", enemyStatsLevelMultiplier,
	                  saveDoc->GetAllocator ());
	object.AddMember ("level", level + incrementLevel,
	                  saveDoc->GetAllocator ());
	saveDoc->AddMember ("game", object, saveDoc->GetAllocator ());

	player->Save (saveDoc);
	userInterface->Save (saveDoc);

	rapidjson::Writer<rapidjson::FileWriteStream> writer (saveStream);
	saveDoc->Accept (writer);

	fclose (saveFile);
}

void
Game::Load ()
{
	HardReset ();

	FILE *saveJsonFile = nullptr;
	fopen_s (&saveJsonFile, "assets/save.json", "r");

	if (saveJsonFile)
	{
		char *readBuffer = new char[65536];
		rapidjson::FileReadStream saveJson (saveJsonFile, readBuffer,
		                                    sizeof (readBuffer));
		saveDoc->ParseStream (saveJson);
		delete[] readBuffer;
		fclose (saveJsonFile);

		enemyStatsLevelMultiplier = (*(
			rapidjson::Value *)(saveDoc))["game"]["enemyStatsLevelMultiplier"]
		                                .GetFloat ();
		level = (*(rapidjson::Value *)(saveDoc))["game"]["level"].GetInt ();

		player->Load (saveDoc);
		userInterface->Load (saveDoc);
	}
	else
	{
		Save ();
	}

	Reset ();
	UnPause ();
}

void
Game::Pause ()
{
	isPaused = true;
};

void
Game::UnPause ()
{
	isPaused = false;
};

void
Game::LoseGame ()
{
	Reset ();
	Pause ();
	userInterface->EnableLoseMenu ();
}

void
Game::WinGame ()
{
	Reset ();
	Pause ();
	userInterface->EnableWinMenu ();
}

void
Game::NewGame ()
{
	HardReset ();
	Reset ();
	UnPause ();
}

void
Game::Quit ()
{
	isRunning = false;
};

void
Game::IncreaseLevel ()
{
	++level;
}

void
Game::ChangeEnemyLevelMultiplier (float multiplier)
{
	enemyStatsLevelMultiplier = multiplier;
}

int
Game::GetLevel () const
{
	return level;
};

bool
Game::IsRunning () const
{
	return isRunning;
};

bool
Game::IsPaused () const
{
	return isPaused;
};