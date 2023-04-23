#include "LoseMenu.h"
#include "../UserInterface.h"

LoseMenu::LoseMenu () {}
LoseMenu::~LoseMenu () {}

LoseMenu::LoseMenu (SDL_Renderer *renderer, TextureManager *textureManager,
                    FontManager *fontManager, Game *game,
                    UserInterface *userInterface)
{
	background = SceneObject (renderer,
	                          textureManager->GetTexture ("darkBackground"));

	label = UILabel (renderer, 0, 20, fontManager->GetFont (FONT_SANS, 72),
	                 "You Lost", { 255, 255, 255 }, 1024);

	buttons.push_back (
		{ Button (renderer, textureManager->GetButtonTexture ("button1"),
	              exitButtonPos,
	              [this, userInterface]
	              {
					  userInterface->EnableMainMenu ();
					  this->enabled = false;
				  }),
	      { { "", UILabel (renderer, exitButtonPos.x, exitButtonPos.y,
	                       fontManager->GetFont (FONT_SANS, 48), "Exit",
	                       { 255, 255, 255 }, exitButtonPos.w,
	                       exitButtonPos.h) } } });

	buttons.push_back (
		{ Button (renderer, textureManager->GetButtonTexture ("button1"),
	              loadButtonPos,
	              [this, game]
	              {
					  game->Load ();
					  this->enabled = false;
				  }),
	      { { "", UILabel (renderer, loadButtonPos.x, loadButtonPos.y,
	                       fontManager->GetFont (FONT_SANS, 32),
	                       "Load Previous Save", { 255, 255, 255 },
	                       loadButtonPos.w, loadButtonPos.h) } } });
}

void
LoseMenu::Render () const
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
LoseMenu::HandleEvents (SDL_Event *event)
{
	if (!enabled)
		return;

	for (auto &button : buttons)
	{
		button.HandleEvents (event, true);
	}
}

void
LoseMenu::Enable ()
{
	enabled = true;
}

bool
LoseMenu::IsEnabled () const
{
	return enabled;
}