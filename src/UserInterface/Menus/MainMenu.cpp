#include "MainMenu.h"

MainMenu::MainMenu () {}
MainMenu::~MainMenu () {}

MainMenu::MainMenu (SDL_Renderer *renderer, TextureManager *textureManager,
                    Game *game, FontManager *fontManager)
	: MainMenu::MainMenu ()
{
	background = SceneObject (textureManager->GetTexture ("darkBackground"),
	                          renderer);

	mainMenuLabel
		= UILabel (renderer, 0, 20, fontManager->GetFont (FONT_SANS, 72),
	               "Defend The Castle", { 255, 255, 255 }, 1024);

	buttons.push_back (
		{ Button (textureManager->GetButtonTexture ("button1"),
	              newGameButtonPos, renderer, [game] { game->NewGame (); }),
	      { { "", UILabel (renderer, newGameButtonPos.x, newGameButtonPos.y,
	                       fontManager->GetFont (FONT_SANS, 48), "New Game",
	                       { 255, 255, 255 }, newGameButtonPos.w,
	                       newGameButtonPos.h) } } });
	buttons.push_back (
		{ Button (textureManager->GetButtonTexture ("button1"),
	              continueButtonPos, renderer, [game] { game->Load (); }),
	      { { "", UILabel (renderer, continueButtonPos.x, continueButtonPos.y,
	                       fontManager->GetFont (FONT_SANS, 48), "Continue",
	                       { 255, 255, 255 }, continueButtonPos.w,
	                       continueButtonPos.h) } } });
	buttons.push_back (
		{ Button (textureManager->GetButtonTexture ("button1"), quitButtonPos,
	              renderer, [game] { game->Quit (); }),
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