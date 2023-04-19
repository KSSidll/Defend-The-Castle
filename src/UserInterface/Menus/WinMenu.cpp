#include "WinMenu.h"

WinMenu::WinMenu () {}
WinMenu::~WinMenu () {}

WinMenu::WinMenu (SDL_Renderer *renderer, Game *game,
                  TextureManager *textureManager, FontManager *fontManager)
	: WinMenu::WinMenu ()
{
	background = SceneObject (textureManager->GetTexture ("darkBackground"),
	                          renderer);

	label = UILabel (renderer, 0, 20, fontManager->GetFont (FONT_SANS, 72),
	                 "Level Cleared", { 255, 255, 255 }, 1024);

	buttons.push_back (
		{ Button (textureManager->GetButtonTexture ("button1"), saveButtonPos,
	              renderer, [game] { game->Save (true); }),
	      { { "", UILabel (renderer, saveButtonPos.x, saveButtonPos.y,
	                       fontManager->GetFont (FONT_SANS, 32), "Save",
	                       { 255, 255, 255 }, saveButtonPos.w,
	                       saveButtonPos.h) } } });

	buttons.push_back (
		{ Button (textureManager->GetButtonTexture ("button1"), shopButtonPos,
	              renderer, [game] { game->ShopMenu (); }),
	      { { "", UILabel (renderer, shopButtonPos.x, shopButtonPos.y,
	                       fontManager->GetFont (FONT_SANS, 32), "Shop",
	                       { 255, 255, 255 }, shopButtonPos.w,
	                       shopButtonPos.h) } } });

	buttons.push_back (
		{ Button (textureManager->GetButtonTexture ("button1"),
	              nextLevelButtonPos, renderer,
	              [game] { game->IncreaseLevel (); }),
	      { { "",
	          UILabel (renderer, nextLevelButtonPos.x, nextLevelButtonPos.y,
	                   fontManager->GetFont (FONT_SANS, 32), "Next Level",
	                   { 255, 255, 255 }, nextLevelButtonPos.w,
	                   nextLevelButtonPos.h) } } });
}

void
WinMenu::Render () const
{
	background.Render ();
	label.Render ();
	for (auto &button : buttons)
	{
		button.Render ();
	}
}

void
WinMenu::HandleEvents (SDL_Event *event)
{
	for (auto &button : buttons)
	{
		button.HandleEvents (event, true);
	}
}
