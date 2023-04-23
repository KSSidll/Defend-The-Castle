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
	pauseMenu
		= new PauseMenu (renderer, textureManager, fontManager, game, this);
	mainMenu = new MainMenu (renderer, textureManager, fontManager, game);
	difficultySelectionMenu = new DifficultySelectionMenu (
		renderer, textureManager, fontManager, game, json);
	winMenu = new WinMenu (renderer, textureManager, fontManager, game, this);
	loseMenu
		= new LoseMenu (renderer, textureManager, fontManager, game, this);
	shopMenu = new ShopMenu (renderer, textureManager, fontManager, this,
	                         player, json);
}

void
UserInterface::Update ()
{
	shopMenu->Update ();
	gameMenu->Update (ShouldGameMenuBeActive ());

	if (!game->Paused ())
		gameMenu->UpdatePlayerStatsLabel ();

	if (bStatUpdate)
	{
		shopMenu->UpdateItemsStats ();
		gameMenu->UpdateEntitiesStatsLabel ();
		bStatUpdate = false;
	}
}

void
UserInterface::Render () const
{
	mainMenu->Render ();
	difficultySelectionMenu->Render ();
	winMenu->Render ();
	loseMenu->Render ();
	shopMenu->Render ();
	pauseMenu->Render ();
	gameMenu->Render ();
}

void
UserInterface::HandleEvents (SDL_Event *event)
{
	mainMenu->HandleEvents (event);
	difficultySelectionMenu->HandleEvents (event);
	winMenu->HandleEvents (event);
	loseMenu->HandleEvents (event);
	shopMenu->HandleEvents (event, &bStatUpdate);
	pauseMenu->HandleEvents (event);
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

void
UserInterface::EnablePauseMenu ()
{
	pauseMenu->Enable ();
}

void
UserInterface::DisablePauseMenu ()
{
	pauseMenu->Disable ();
}

void
UserInterface::EnableMainMenu ()
{
	mainMenu->Enable ();
}

void
UserInterface::EnableDifficultySelectionMenu ()
{
	difficultySelectionMenu->Enable ();
}

void
UserInterface::EnableWinMenu ()
{
	winMenu->Enable ();
}

void
UserInterface::EnableLoseMenu ()
{
	loseMenu->Enable ();
}

void
UserInterface::EnableShopMenu ()
{
	shopMenu->Enable ();
}

bool
UserInterface::ShouldGameMenuBeActive () const
{
	return !(pauseMenu->IsEnabled () || mainMenu->IsEnabled ()
	         || difficultySelectionMenu->IsEnabled () || winMenu->IsEnabled ()
	         || loseMenu->IsEnabled () || shopMenu->IsEnabled ());
}