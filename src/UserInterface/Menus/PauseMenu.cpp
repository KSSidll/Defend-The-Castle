#include "PauseMenu.h"
#include "../UserInterface.h"

PauseMenu::PauseMenu () {}
PauseMenu::~PauseMenu () {}

PauseMenu::PauseMenu (SDL_Renderer *renderer, TextureManager *textureManager,
                      FontManager *fontManager, Game *game,
                      UserInterface *userInterface)
{
	background = SceneObject (renderer,
	                          textureManager->GetTexture ("darkBackground"));
	label = UILabel (renderer, 0, 50, fontManager->GetFont (FONT_SANS, 48),
	                 "Paused", { 255, 255, 255 }, 1024);

	buttons.push_back (
		{ Button (renderer, textureManager->GetButtonTexture ("button1"),
	              resumeButtonPos,
	              [this, game]
	              {
					  game->UnPause ();
					  this->enabled = false;
				  }),
	      { { "", UILabel (renderer, resumeButtonPos.x, resumeButtonPos.y,
	                       fontManager->GetFont (FONT_SANS, 32), "Resume",
	                       { 255, 255, 255 }, resumeButtonPos.w,
	                       resumeButtonPos.h) } } });
	buttons.push_back (
		{ Button (renderer, textureManager->GetButtonTexture ("button1"),
	              exitButtonPos,
	              [this, userInterface]
	              {
					  userInterface->EnableMainMenu ();
					  this->enabled = false;
				  }),
	      { { "", UILabel (renderer, exitButtonPos.x, exitButtonPos.y,
	                       fontManager->GetFont (FONT_SANS, 32), "Exit",
	                       { 255, 255, 255 }, exitButtonPos.w,
	                       exitButtonPos.h) } } });
}

void
PauseMenu::Render () const
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
PauseMenu::HandleEvents (SDL_Event *event)
{
	if (!enabled)
		return;

	for (auto &button : buttons)
	{
		button.HandleEvents (event, true);
	}
}

void
PauseMenu::Enable ()
{
	enabled = true;
}

void
PauseMenu::Disable ()
{
	enabled = false;
}

bool
PauseMenu::IsEnabled () const
{
	return enabled;
}