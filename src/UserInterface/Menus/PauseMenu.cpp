#include "PauseMenu.h"

PauseMenu::PauseMenu () {}
PauseMenu::~PauseMenu () {}

PauseMenu::PauseMenu (SDL_Renderer *renderer, TextureManager *textureManager,
                      FontManager *fontManager, Game *game)
	: PauseMenu::PauseMenu ()
{
	background = SceneObject (renderer,
	                          textureManager->GetTexture ("darkBackground"));
	label = UILabel (renderer, 0, 50, fontManager->GetFont (FONT_SANS, 48),
	                 "Paused", { 255, 255, 255 }, 1024);

	buttons.push_back (
		{ Button (renderer, textureManager->GetButtonTexture ("button1"),
	              resumeButtonPos, [game] { game->UnPause (); }),
	      { { "", UILabel (renderer, resumeButtonPos.x, resumeButtonPos.y,
	                       fontManager->GetFont (FONT_SANS, 32), "Resume",
	                       { 255, 255, 255 }, resumeButtonPos.w,
	                       resumeButtonPos.h) } } });
	buttons.push_back (
		{ Button (renderer, textureManager->GetButtonTexture ("button1"),
	              exitButtonPos, [game] { game->MainMenu (); }),
	      { { "", UILabel (renderer, exitButtonPos.x, exitButtonPos.y,
	                       fontManager->GetFont (FONT_SANS, 32), "Exit",
	                       { 255, 255, 255 }, exitButtonPos.w,
	                       exitButtonPos.h) } } });
}

void
PauseMenu::Render () const
{
	background.Render ();
	label.Render ();
	for (const auto &button : buttons)
	{
		button.Render ();
	}
}

void
PauseMenu::HandleEvents (SDL_Event *event)
{
	for (auto &button : buttons)
	{
		button.HandleEvents (event, true);
	}
}