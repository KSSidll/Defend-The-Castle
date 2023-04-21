#include "GameMenu.h"
#include "../../Managers/SummonDungeon.h"

GameMenu::GameMenu ()
{
	game = nullptr;
	player = nullptr;
	json = nullptr;
}

GameMenu::~GameMenu ()
{
	json = nullptr;
	player = nullptr;
	game = nullptr;
}

GameMenu::GameMenu (SDL_Renderer *renderer, TextureManager *textureManager,
                    FontManager *fontManager, const Game *game,
                    SummonDungeon *dungeon, const Player *player,
                    const rapidjson::Value *json)
{
	this->game = game;
	this->player = player;
	this->json = json;

	gameInfoBackground
		= SceneObject (renderer, textureManager->GetTexture ("darkBackground"),
	                   gameInfoBackgroundPos);

	playerFujika = UILabel (
		renderer, (gameInfoBackgroundPos.w / 3 * 0), gameInfoBackgroundPos.y,
		fontManager->GetFont (FONT_SANS, 24),
		"Fujika " + std::to_string (player->GetFujika ()) + " / "
			+ std::to_string (player->GetFujikaLimit ()),
		{ 255, 255, 255 }, gameInfoBackgroundPos.w / 3,
		gameInfoBackgroundPos.h);
	levelInfo = UILabel (
		renderer, (gameInfoBackgroundPos.w / 3 * 1), gameInfoBackgroundPos.y,
		fontManager->GetFont (FONT_SANS, 24),
		"Level " + std::to_string (game->Level () + 1), { 255, 255, 255 },
		gameInfoBackgroundPos.w / 3, gameInfoBackgroundPos.h);
	playerFuko = UILabel (renderer, (gameInfoBackgroundPos.w / 3 * 2),
	                      gameInfoBackgroundPos.y,
	                      fontManager->GetFont (FONT_SANS, 24),
	                      "Fuko " + std::to_string (player->GetFuko ()) + " / "
	                          + std::to_string (player->GetFukoLimit ()),
	                      { 255, 255, 255 }, gameInfoBackgroundPos.w / 3,
	                      gameInfoBackgroundPos.h);

	int entityCounter = 0;
	int rectW
		= gameInfoBackgroundPos.w / ((*json)["summons"].MemberCount () + 1);
	SDL_Rect tmp_rect = { 0, 543, rectW, 225 };

	for (const auto &entity : (*json)["summons"].GetObject ())
	{
		std::string tmp_statText = "";
		for (const auto &stat : entity.value.GetObject ())
		{
			auto itr = (*json)["lang"].FindMember (stat.name.GetString ());
			if (itr != (*json)["lang"].MemberEnd ())
			{
				tmp_statText.append (std::string (itr->value.GetString ())
				                     + ": "
				                     + std::to_string (stat.value.GetInt ()));
				tmp_statText.append ("\n");
			}
		}
		std::string tmp_name = entity.name.GetString ();
		tmp_name[0] = toupper (tmp_name[0]);
		UILabel NameLabel = UILabel (renderer, tmp_rect.x + 5, tmp_rect.y + 5,
		                             fontManager->GetFont (FONT_SANS, 24),
		                             tmp_name, { 255, 255, 255 }, tmp_rect.w);
		UILabel StatsLabel
			= UILabel (renderer, tmp_rect.x + 5,
		               tmp_rect.y + NameLabel.GetPosition ().h + 5,
		               fontManager->GetFont (FONT_SANS, 16), tmp_statText,
		               { 255, 255, 255 });
		Button button = Button (
			renderer, textureManager->GetButtonTexture ("button2"), tmp_rect,
			[dungeon, json, type = entity.name.GetString ()]
			{ dungeon->SummonObject ((*json)["summons"][type]); });

		buttons.push_back (
			{ { button, { { "name", NameLabel }, { "stats", StatsLabel } } },
		      entity.name.GetString () });

		++entityCounter;
		tmp_rect.x = entityCounter * rectW;
	}

	tmp_rect.w = gameInfoBackgroundPos.w - (rectW * entityCounter);

	enemyStatsBackground = SceneObject (
		renderer, textureManager->GetTexture ("darkBackground"), tmp_rect);
	enemyNameLabel = UILabel (renderer, tmp_rect.x + 5, tmp_rect.y + 5,
	                          fontManager->GetFont (FONT_SANS, 24), "Enemy",
	                          { 255, 255, 255 }, tmp_rect.w);
	{
		std::string tmp_statText = "";
		for (const auto &stat : (*json)["enemy"].GetObject ())
		{
			auto itr = (*json)["lang"].FindMember (stat.name.GetString ());
			if (itr != (*json)["lang"].MemberEnd ())
			{
				tmp_statText.append (std::string (itr->value.GetString ())
				                     + ": "
				                     + std::to_string (stat.value.GetInt ()));
				tmp_statText.append ("\n");
			}
		}
		enemyStatsLabel
			= UILabel (renderer, tmp_rect.x + 5,
		               tmp_rect.y + enemyNameLabel.GetPosition ().h,
		               fontManager->GetFont (FONT_SANS, 16), tmp_statText,
		               { 255, 255, 255 });
	}
}

void
GameMenu::Render () const
{
	for (const auto &button : buttons)
	{
		button.button.Render ();
	}

	gameInfoBackground.Render ();
	enemyStatsBackground.Render ();
	enemyNameLabel.Render ();
	enemyStatsLabel.Render ();

	levelInfo.Render ();
	playerFujika.Render ();
	playerFuko.Render ();
}

void
GameMenu::HandleEvents (SDL_Event *event)
{
	for (auto &button : buttons)
	{
		button.button.HandleEvents (event, true);
	}
}

void UpdateEnemyStatsLabel ();
void UpdateEntitiesStatsLabel ();

void
GameMenu::Reset (float multiplier)
{
	UpdateEnemyStatsLabel (multiplier);
	UpdateEntitiesStatsLabel ();
}

void
GameMenu::Update (bool bStatUpdate)
{
	playerFujika.ChangeText (("Fujika " + std::to_string (player->GetFujika ())
	                          + " / "
	                          + std::to_string (player->GetFujikaLimit ()))
	                             .c_str ());
	levelInfo.ChangeText (
		("Level " + std::to_string (game->Level () + 1)).c_str ());
	playerFuko.ChangeText (("Fuko " + std::to_string (player->GetFuko ())
	                        + " / " + std::to_string (player->GetFukoLimit ()))
	                           .c_str ());

	if (bStatUpdate)
		UpdateEntitiesStatsLabel ();
}

void
GameMenu::UpdateEnemyStatsLabel (float multiplier)
{
	std::string tmp_statText = "";
	for (const auto &stat : (*json)["enemy"].GetObject ())
	{
		auto itr = (*json)["lang"].FindMember (stat.name.GetString ());
		if (itr != (*json)["lang"].MemberEnd ())
		{
			if (std::string (stat.name.GetString ()) == "range")
				tmp_statText.append (
					std::string (itr->value.GetString ()) + ": "
					+ std::to_string ((int)(stat.value.GetInt ())));
			else
				tmp_statText.append (
					std::string (itr->value.GetString ()) + ": "
					+ std::to_string (
						(int)(stat.value.GetInt () * multiplier)));

			tmp_statText.append ("\n");
		}
	}
	enemyStatsLabel.ChangeText (tmp_statText.c_str ());
}

void
GameMenu::UpdateEntitiesStatsLabel ()
{
	for (auto &button : buttons)
	{
		std::string tmp_statText = "";
		for (const auto &stat :
		     (*json)["summons"][(const char *)(button.entity_type)]
		         .GetObject ())
		{
			auto itr = (*json)["lang"].FindMember (stat.name.GetString ());
			if (itr != (*json)["lang"].MemberEnd ())
			{
				tmp_statText.append (std::string (itr->value.GetString ())
				                     + ": "
				                     + std::to_string (stat.value.GetInt ()));
				tmp_statText.append ("\n");
			}
		}

		button.button.ChangeText ("stats", tmp_statText.c_str ());
	}
}