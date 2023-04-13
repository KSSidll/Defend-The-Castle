#include "Game.h"
#include "../Managers/Player.h"
#include "../Managers/SummonDungeon.h"
#include "../Managers/TextureManager.h"
#include "../Objects/Enemy.h"
#include "../Objects/PlayerSummon.h"
#include "../UserInterface/UserInterface.h"
#include <cmath>
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/writer.h>

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
	background = nullptr;
}

Game::~Game ()
{
	background = nullptr;
	enemy = nullptr;
	player = nullptr;
	userInterface = nullptr;
	textureManager = nullptr;
	summonDungeon = nullptr;
	saveDoc = nullptr;
	objectsDoc = nullptr;
	renderer = nullptr;
	window = nullptr;
}

void
Game::Init (const char *title, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;

	objectsDoc = new rapidjson::Document ();

	FILE *objectsJsonFile = fopen ("assets/objects.json", "r");
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

	for (auto &texture : (*objectsDoc)["textures"].GetArray ())
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

	background = new SceneObject (
		textureManager->GetTexture ((*objectsDoc)["background"]["textureSrc"]),
		renderer);

	summonDungeon = new SummonDungeon (textureManager, renderer, player);

	enemy = new Enemy (
		textureManager->GetTexture ((*objectsDoc)["enemy"]["textureSrc"]),
		(*objectsDoc)["enemy"], renderer);

	userInterface = new UserInterface (objectsDoc, summonDungeon, renderer,
	                                   textureManager, this, player);
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
			if (isPaused && !menuFlag)
				UnPause ();
			else
				Pause ();
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

	if (enemy->KillPending ())
		WinMenu ();

	if (enemy->GetPosition () <= -250)
		LoseGame ();
}

void
Game::Render ()
{
	SDL_RenderClear (renderer);
	background->Render ();

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
	if (enemy->Alive ())
		for (auto &summon : *(summonDungeon->getObjectArray ()))
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
		for (auto &summon : *(summonDungeon->getObjectArray ()))
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
	UnPause ();
}

void
Game::Save (bool incrementLevel)
{
	FILE *saveFile = fopen ("assets/save.json", "w");

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

	if (FILE *saveJsonFile = fopen ("assets/save.json", "r"))
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
	Start ();
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
Game::Quit ()
{
	isRunning = false;
};

void
Game::IncreaseLevel ()
{
	++level;
	Start ();
}

void
Game::ChangeEnemyLevelMultiplier (float multiplier)
{
	enemyStatsLevelMultiplier = multiplier;
	Start ();
}

bool
Game::Running ()
{
	return isRunning;
};

bool
Game::Paused ()
{
	return isPaused;
};

int
Game::Level ()
{
	return level;
};

void
Game::LoseGame ()
{
	ResetMenus ();
	Reset ();
	loseMenu = true;
	isPaused = true;
	menuFlag = true;
}

void
Game::NewGame ()
{
	level = 0;
	ResetMenus ();
	HardReset ();
	Reset ();
	isPaused = true;
	difficultyMenu = true;
	menuFlag = true;
}

void
Game::Start ()
{
	ResetMenus ();
}

void
Game::MainMenu ()
{
	ResetMenus ();
	HardReset ();
	mainMenu = true;
	isPaused = true;
	menuFlag = true;
}

void
Game::WinMenu ()
{
	Reset ();
	ResetMenus ();
	winMenu = true;
	isPaused = true;
	menuFlag = true;
}

void
Game::ShopMenu ()
{
	ResetMenus ();
	shopMenu = true;
	isPaused = true;
	menuFlag = true;
}

void
Game::ResetMenus ()
{
	mainMenu = false;
	isPaused = false;
	difficultyMenu = false;
	winMenu = false;
	loseMenu = false;
	shopMenu = false;
	menuFlag = false;
}

bool
Game::isMainMenu ()
{
	return mainMenu;
};

bool
Game::isDifficultyMenu ()
{
	return difficultyMenu;
};

bool
Game::isWinMenu ()
{
	return winMenu;
};

bool
Game::isLoseMenu ()
{
	return loseMenu;
};

bool
Game::isShopMenu ()
{
	return shopMenu;
};