#include "DifficultySelectionMenu.h"

DifficultySelectionMenu::DifficultySelectionMenu () {}
DifficultySelectionMenu::~DifficultySelectionMenu () {}

DifficultySelectionMenu::DifficultySelectionMenu (
	SDL_Renderer *renderer, Game *game, TextureManager *textureManager,
	const rapidjson::Value *json, FontManager *fontManager)
	: DifficultySelectionMenu::DifficultySelectionMenu ()
{
	easy = (*json)["difficulties"]["easy"].GetFloat ();
	medium = (*json)["difficulties"]["medium"].GetFloat ();
	hard = (*json)["difficulties"]["hard"].GetFloat ();

	background = SceneObject (textureManager->GetTexture ("darkBackground"),
	                          renderer);
	label = UILabel (renderer, 0, 50, fontManager->GetFont (FONT_SANS, 48),
	                 "Select Difficulty", { 255, 255, 255 }, 1024);

	buttons.push_back (
		{ Button (textureManager->GetButtonTexture ("button1"), easyButtonPos,
	              renderer,
	              [game, easy = &easy]
	              { game->ChangeEnemyLevelMultiplier (*easy); }),
	      { { "", UILabel (renderer, easyButtonPos.x, easyButtonPos.y,
	                       fontManager->GetFont (FONT_SANS, 32), "Easy",
	                       { 255, 255, 255 }, easyButtonPos.w,
	                       easyButtonPos.h) } } });

	buttons.push_back (
		{ Button (textureManager->GetButtonTexture ("button1"),
	              mediumButtonPos, renderer,
	              [game, medium = &medium]
	              { game->ChangeEnemyLevelMultiplier (*medium); }),
	      { { "", UILabel (renderer, mediumButtonPos.x, mediumButtonPos.y,
	                       fontManager->GetFont (FONT_SANS, 32), "Medium",
	                       { 255, 255, 255 }, mediumButtonPos.w,
	                       mediumButtonPos.h) } } });

	buttons.push_back (
		{ Button (textureManager->GetButtonTexture ("button1"), hardButtonPos,
	              renderer,
	              [game, hard = &hard]
	              { game->ChangeEnemyLevelMultiplier (*hard); }),
	      { { "", UILabel (renderer, hardButtonPos.x, hardButtonPos.y,
	                       fontManager->GetFont (FONT_SANS, 32), "Hard",
	                       { 255, 255, 255 }, hardButtonPos.w,
	                       hardButtonPos.h) } } });
}

void
DifficultySelectionMenu::Render () const
{
	background.Render ();
	label.Render ();
	for (const auto &button : buttons)
	{
		button.Render ();
	}
}

void
DifficultySelectionMenu::HandleEvents (SDL_Event *event)
{
	for (auto &button : buttons)
	{
		button.HandleEvents (event, true);
	}
}