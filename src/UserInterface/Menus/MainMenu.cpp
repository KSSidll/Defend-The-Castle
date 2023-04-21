#include "MainMenu.h"

MainMenu::MainMenu () {}
MainMenu::~MainMenu () {}

MainMenu::MainMenu (SDL_Renderer *renderer, TextureManager *textureManager,
                    FontManager *fontManager, Game *game)
	: MainMenu::MainMenu ()
{
	background = SceneObject (renderer,
	                          textureManager->GetTexture ("darkBackground"));

	mainMenuLabel
		= UILabel (renderer, 0, 20, fontManager->GetFont (FONT_SANS, 72),
	               "Defend The Castle", { 255, 255, 255 }, 1024);

	buttons.push_back (
		{ Button (renderer, textureManager->GetButtonTexture ("button1"),
	              newGameButtonPos, [game] { game->NewGame (); }),
	      { { "", UILabel (renderer, newGameButtonPos.x, newGameButtonPos.y,
	                       fontManager->GetFont (FONT_SANS, 48), "New Game",
	                       { 255, 255, 255 }, newGameButtonPos.w,
	                       newGameButtonPos.h) } } });
	buttons.push_back (
		{ Button (renderer, textureManager->GetButtonTexture ("button1"),
	              continueButtonPos, [game] { game->Load (); }),
	      { { "", UILabel (renderer, continueButtonPos.x, continueButtonPos.y,
	                       fontManager->GetFont (FONT_SANS, 48), "Continue",
	                       { 255, 255, 255 }, continueButtonPos.w,
	                       continueButtonPos.h) } } });
	buttons.push_back (
		{ Button (renderer, textureManager->GetButtonTexture ("button1"),
	              quitButtonPos, [game] { game->Quit (); }),
	      { { "", UILabel (renderer, quitButtonPos.x, quitButtonPos.y,
	                       fontManager->GetFont (FONT_SANS, 32), "Quit",
	                       { 255, 255, 255 }, quitButtonPos.w,
	                       quitButtonPos.h) } } });
}

void
MainMenu::Render () const
{
	background.Render ();
	mainMenuLabel.Render ();
	for (const auto &button : buttons)
	{
		button.Render ();
	}
}

void
MainMenu::HandleEvents (SDL_Event *event)
{
	for (auto &button : buttons)
	{
		button.HandleEvents (event, true);
	}
}