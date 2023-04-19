#include "LoseMenu.h"

LoseMenu::LoseMenu () {}
LoseMenu::~LoseMenu () {}

LoseMenu::LoseMenu (SDL_Renderer *renderer, Game *game,
                    TextureManager *textureManager, FontManager *fontManager)
	: LoseMenu::LoseMenu ()
{
	background = SceneObject (textureManager->GetTexture ("darkBackground"),
	                          renderer);

	label = UILabel (renderer, 0, 20, fontManager->GetFont (FONT_SANS, 72),
	                 "You Lost", { 255, 255, 255 }, 1024);

	buttons.push_back (
		{ Button (textureManager->GetButtonTexture ("button1"), exitButtonPos,
	              renderer, [game] { game->MainMenu (); }),
	      { { "", UILabel (renderer, exitButtonPos.x, exitButtonPos.y,
	                       fontManager->GetFont (FONT_SANS, 48), "Exit",
	                       { 255, 255, 255 }, exitButtonPos.w,
	                       exitButtonPos.h) } } });

	buttons.push_back (
		{ Button (textureManager->GetButtonTexture ("button1"), loadButtonPos,
	              renderer, [game] { game->Load (); }),
	      { { "", UILabel (renderer, loadButtonPos.x, loadButtonPos.y,
	                       fontManager->GetFont (FONT_SANS, 32),
	                       "Load Previous Save", { 255, 255, 255 },
	                       loadButtonPos.w, loadButtonPos.h) } } });
}

void
LoseMenu::Render () const
{
	background.Render ();
	label.Render ();
	for (auto &button : buttons)
	{
		button.Render ();
	}
}

void
LoseMenu::HandleEvents (SDL_Event *event)
{
	for (auto &button : buttons)
	{
		button.HandleEvents (event, true);
	}
}