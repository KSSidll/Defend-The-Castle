#include "DifficultySelectionMenu.h"
#include "../Engine/Game.h"
#include "../Managers/TextureManager.h"
#include "../Objects/SceneObject.h"
#include "Button.h"
#include "UILabel.h"
#include <rapidjson/document.h>

DifficultySelectionMenu::DifficultySelectionMenu ()
{
	game = nullptr;
	renderer = nullptr;
	background = nullptr;
	label = nullptr;
	easy = nullptr;
	medium = nullptr;
	hard = nullptr;
}

DifficultySelectionMenu::~DifficultySelectionMenu ()
{
	hard = nullptr;
	medium = nullptr;
	easy = nullptr;
	label = nullptr;
	background = nullptr;
	renderer = nullptr;
	game = nullptr;
}

DifficultySelectionMenu::DifficultySelectionMenu (
	SDL_Renderer *renderer, Game *game, TextureManager *textureManager,
	rapidjson::Value *json)
	: DifficultySelectionMenu::DifficultySelectionMenu ()
{
	this->game = game;
	this->renderer = renderer;

	easy = new float;
	*easy = (*json)["difficulties"]["easy"].GetFloat ();

	medium = new float;
	*medium = (*json)["difficulties"]["medium"].GetFloat ();

	hard = new float;
	*hard = (*json)["difficulties"]["hard"].GetFloat ();

	background = new SceneObject (
		textureManager->GetTexture ("darkBackground"), renderer);
	label = new UILabel (renderer, 0, 50, "assets/fonts/Sans.ttf", 48,
	                     "Select Difficulty", { 255, 255, 255 }, 1024);

	buttons.push_back (
		{ Button (textureManager->GetButtonTexture ("button1"), easyButtonPos,
	              renderer, (void *)easy,
	              [] (Game *game, float *number)
	              { game->ChangeEnemyLevelMultiplier (*number); }),
	      { { "",
	          UILabel (renderer, easyButtonPos.x, easyButtonPos.y,
	                   "assets/fonts/Sans.ttf", 32, "Easy", { 255, 255, 255 },
	                   easyButtonPos.w, easyButtonPos.h) } } });

	buttons.push_back (
		{ Button (textureManager->GetButtonTexture ("button1"),
	              mediumButtonPos, renderer, (void *)medium,
	              [] (Game *game, float *number)
	              { game->ChangeEnemyLevelMultiplier (*number); }),
	      { { "", UILabel (renderer, mediumButtonPos.x, mediumButtonPos.y,
	                       "assets/fonts/Sans.ttf", 32, "Medium",
	                       { 255, 255, 255 }, mediumButtonPos.w,
	                       mediumButtonPos.h) } } });

	buttons.push_back (
		{ Button (textureManager->GetButtonTexture ("button1"), hardButtonPos,
	              renderer, (void *)hard,
	              [] (Game *game, float *number)
	              { game->ChangeEnemyLevelMultiplier (*number); }),
	      { { "",
	          UILabel (renderer, hardButtonPos.x, hardButtonPos.y,
	                   "assets/fonts/Sans.ttf", 32, "Hard", { 255, 255, 255 },
	                   hardButtonPos.w, hardButtonPos.h) } } });
}

void
DifficultySelectionMenu::Render ()
{
	background->Render ();
	label->Render ();
	for (auto &button : buttons)
	{
		button.Render ();
	}
}

void
DifficultySelectionMenu::HandleEvents (SDL_Event *event)
{
	for (auto &button : buttons)
	{
		if (button.HandleEvents (event))
			button.button.game_numbered (game,
			                             (float *)button.button.GetArg ());
	}
}