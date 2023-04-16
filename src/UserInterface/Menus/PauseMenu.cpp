#include "PauseMenu.h"
#include "../../Game.h"
#include "../../Managers/TextureManager.h"
#include "../../Objects/SceneObject.h"
#include "../Components/Button.h"
#include "../Components/UILabel.h"

PauseMenu::PauseMenu ()
{
	game = nullptr;
	renderer = nullptr;
	background = nullptr;
	label = nullptr;
}

PauseMenu::~PauseMenu ()
{
	label = nullptr;
	background = nullptr;
	renderer = nullptr;
	game = nullptr;
}

PauseMenu::PauseMenu (SDL_Renderer *renderer, Game *game,
                      TextureManager *textureManager)
	: PauseMenu::PauseMenu ()
{
	this->game = game;
	this->renderer = renderer;

	background = new SceneObject (
		textureManager->GetTexture ("darkBackground"), renderer);
	label = new UILabel (renderer, 0, 50, "assets/fonts/Sans.ttf", 48,
	                     "Paused", { 255, 255, 255 }, 1024);

	// buttons = new std::deque<LabeledButton> (2);

	buttons.push_back (
		{ Button (textureManager->GetButtonTexture ("button1"),
	              resumeButtonPos, renderer,
	              [] (Game *game) { game->UnPause (); }),
	      { { "", UILabel (renderer, resumeButtonPos.x, resumeButtonPos.y,
	                       "assets/fonts/Sans.ttf", 32, "Resume",
	                       { 255, 255, 255 }, resumeButtonPos.w,
	                       resumeButtonPos.h) } } });
	buttons.push_back (
		{ Button (textureManager->GetButtonTexture ("button1"), exitButtonPos,
	              renderer, [] (Game *game) { game->MainMenu (); }),
	      { { "",
	          UILabel (renderer, exitButtonPos.x, exitButtonPos.y,
	                   "assets/fonts/Sans.ttf", 32, "Exit", { 255, 255, 255 },
	                   exitButtonPos.w, exitButtonPos.h) } } });
}

void
PauseMenu::Render ()
{
	background->Render ();
	label->Render ();
	for (auto &button : buttons)
	{
		button.Render ();
	}
}

void
PauseMenu::HandleEvents (SDL_Event *event)
{
	for (auto &button : buttons)
	{
		if (button.HandleEvents (event))
			button.button.game (game);
	}
}