#include "DifficultySelectionMenu.h"

DifficultySelectionMenu::DifficultySelectionMenu () {}
DifficultySelectionMenu::~DifficultySelectionMenu () {}

DifficultySelectionMenu::DifficultySelectionMenu (
	SDL_Renderer *renderer, TextureManager *textureManager,
	FontManager *fontManager, Game *game, const rapidjson::Value *json)
{
	enabled = false;
	easy = (*json)["difficulties"]["easy"].GetFloat ();
	medium = (*json)["difficulties"]["medium"].GetFloat ();
	hard = (*json)["difficulties"]["hard"].GetFloat ();

	background = SceneObject (renderer,
	                          textureManager->GetTexture ("darkBackground"));
	label = UILabel (renderer, 0, 50, fontManager->GetFont (FONT_SANS, 48),
	                 "Select Difficulty", { 255, 255, 255 }, 1024);

	buttons.push_back (
		{ Button (renderer, textureManager->GetButtonTexture ("button1"),
	              easyButtonPos,
	              [this, game, easy = &easy]
	              {
					  game->ChangeEnemyLevelMultiplier (*easy);
					  this->enabled = false;
				  }),
	      { { "", UILabel (renderer, easyButtonPos.x, easyButtonPos.y,
	                       fontManager->GetFont (FONT_SANS, 32), "Easy",
	                       { 255, 255, 255 }, easyButtonPos.w,
	                       easyButtonPos.h) } } });

	buttons.push_back (
		{ Button (renderer, textureManager->GetButtonTexture ("button1"),
	              mediumButtonPos,
	              [this, game, medium = &medium]
	              {
					  game->ChangeEnemyLevelMultiplier (*medium);
					  this->enabled = false;
				  }),
	      { { "", UILabel (renderer, mediumButtonPos.x, mediumButtonPos.y,
	                       fontManager->GetFont (FONT_SANS, 32), "Medium",
	                       { 255, 255, 255 }, mediumButtonPos.w,
	                       mediumButtonPos.h) } } });

	buttons.push_back (
		{ Button (renderer, textureManager->GetButtonTexture ("button1"),
	              hardButtonPos,
	              [this, game, hard = &hard]
	              {
					  game->ChangeEnemyLevelMultiplier (*hard);
					  this->enabled = false;
				  }),
	      { { "", UILabel (renderer, hardButtonPos.x, hardButtonPos.y,
	                       fontManager->GetFont (FONT_SANS, 32), "Hard",
	                       { 255, 255, 255 }, hardButtonPos.w,
	                       hardButtonPos.h) } } });
}

void
DifficultySelectionMenu::Render () const
{
	if (!enabled)
		return;

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
	if (!enabled)
		return;

	for (auto &button : buttons)
	{
		button.HandleEvents (event, true);
	}
}

void
DifficultySelectionMenu::Enable ()
{
	enabled = true;
}

bool
DifficultySelectionMenu::IsEnabled () const
{
	return enabled;
}