#include "UserInterface.h"

UserInterface::UserInterface ()
{
	game = nullptr;
	fontManager = nullptr;
	gameMenu = nullptr;
	pauseMenu = nullptr;
	mainMenu = nullptr;
	difficultySelectionMenu = nullptr;
	winMenu = nullptr;
	loseMenu = nullptr;
	shopMenu = nullptr;
}
UserInterface::~UserInterface ()
{
	if (shopMenu)
		delete shopMenu;
	if (loseMenu)
		delete loseMenu;
	if (winMenu)
		delete winMenu;
	if (difficultySelectionMenu)
		delete difficultySelectionMenu;
	if (mainMenu)
		delete mainMenu;
	if (pauseMenu)
		delete pauseMenu;
	if (gameMenu)
		delete gameMenu;
	if (fontManager)
		delete fontManager;

	game = nullptr;
}

UserInterface::UserInterface (SDL_Renderer *renderer,
                              TextureManager *textureManager, Game *game,
                              SummonDungeon *dungeon, Player *player,
                              rapidjson::Value *json)
	: UserInterface::UserInterface ()
{
	this->game = game;
	fontManager = new FontManager ();
	gameMenu = new GameMenu (renderer, textureManager, fontManager, game,
	                         dungeon, player, json);
	pauseMenu = new PauseMenu (renderer, textureManager, fontManager, game);
	mainMenu = new MainMenu (renderer, textureManager, fontManager, game);
	difficultySelectionMenu = new DifficultySelectionMenu (
		renderer, textureManager, fontManager, game, json);
	winMenu = new WinMenu (renderer, textureManager, fontManager, game);
	loseMenu = new LoseMenu (renderer, textureManager, fontManager, game);
	shopMenu = new ShopMenu (renderer, textureManager, fontManager, game,
	                         player, json);
}

void
UserInterface::Update ()
{
	if (game->isShopMenu ())
		shopMenu->Update ();

	else if (!game->Paused ())
		gameMenu->Update ();

	if (bStatUpdate)
	{
		shopMenu->Update (true);
		gameMenu->Update (true);
		bStatUpdate = false;
	}
}

void
UserInterface::Render () const
{
	if (game->isMainMenu ())
		mainMenu->Render ();

	else if (game->isDifficultyMenu ())
		difficultySelectionMenu->Render ();

	else if (game->isWinMenu ())
		winMenu->Render ();

	else if (game->isLoseMenu ())
		loseMenu->Render ();

	else if (game->isShopMenu ())
		shopMenu->Render ();

	else if (game->Paused ())
		pauseMenu->Render ();

	else
		gameMenu->Render ();
}

void
UserInterface::HandleEvents (SDL_Event *event)
{
	if (game->isMainMenu ())
		mainMenu->HandleEvents (event);

	else if (game->isDifficultyMenu ())
		difficultySelectionMenu->HandleEvents (event);

	else if (game->isWinMenu ())
		winMenu->HandleEvents (event);

	else if (game->isLoseMenu ())
		loseMenu->HandleEvents (event);

	else if (game->isShopMenu ())
		shopMenu->HandleEvents (event, &bStatUpdate);

	else if (game->Paused ())
		pauseMenu->HandleEvents (event);

	else
		gameMenu->HandleEvents (event);
}

void
UserInterface::Reset (float multiplier)
{
	gameMenu->Reset (multiplier);
}

void
UserInterface::HardReset ()
{
	bStatUpdate = true;

	shopMenu->Reset ();

	Update ();
}

void
UserInterface::Save (rapidjson::Document *saveJson) const
{
	shopMenu->Save (saveJson);
}

void
UserInterface::Load (const rapidjson::Value *saveJson)
{
	shopMenu->Load (saveJson);
	bStatUpdate = true;
}