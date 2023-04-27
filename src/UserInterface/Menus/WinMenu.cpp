#include "WinMenu.h"
#include "../UserInterface.h"

WinMenu::WinMenu () {}
WinMenu::~WinMenu () {}

WinMenu::WinMenu (SDL_Renderer *renderer, TextureManager *textureManager,
                  FontManager *fontManager, Game *game,
                  UserInterface *userInterface)
{
	background = SceneObject (renderer,
	                          textureManager->GetTexture ("darkBackground"));

	label = UILabel (renderer, 0, 20, fontManager->GetFont (FONT_SANS, 72),
	                 "Level Cleared", { 255, 255, 255 }, 1024);

	buttons.push_back (
		{ Button (renderer, textureManager->GetButtonTexture ("button1"),
	              saveButtonPos, [game] { game->Save (true); }),
	      { { "", UILabel (renderer, saveButtonPos.x, saveButtonPos.y,
	                       fontManager->GetFont (FONT_SANS, 32), "Save",
	                       { 255, 255, 255 }, saveButtonPos.w,
	                       saveButtonPos.h) } } });

	buttons.push_back (
		{ Button (renderer, textureManager->GetButtonTexture ("button1"),
	              shopButtonPos,
	              [this, userInterface]
	              {
					  userInterface->EnableShopMenu ();
					  this->enabled = false;
				  }),
	      { { "", UILabel (renderer, shopButtonPos.x, shopButtonPos.y,
	                       fontManager->GetFont (FONT_SANS, 32), "Shop",
	                       { 255, 255, 255 }, shopButtonPos.w,
	                       shopButtonPos.h) } } });

	buttons.push_back (
		{ Button (renderer, textureManager->GetButtonTexture ("button1"),
	              nextLevelButtonPos,
	              [this, game]
	              {
					  game->IncreaseLevel ();
					  game->UnPause ();
					  this->enabled = false;
				  }),
	      { { "",
	          UILabel (renderer, nextLevelButtonPos.x, nextLevelButtonPos.y,
	                   fontManager->GetFont (FONT_SANS, 32), "Next Level",
	                   { 255, 255, 255 }, nextLevelButtonPos.w,
	                   nextLevelButtonPos.h) } } });
}

void
WinMenu::Render () const
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
WinMenu::HandleEvents (SDL_Event *event)
{
	if (!enabled)
		return;

	for (auto &button : buttons)
	{
		button.HandleEvents (event, true);
	}
}

void
WinMenu::Enable ()
{
	enabled = true;
}

bool
WinMenu::IsEnabled () const
{
	return enabled;
}