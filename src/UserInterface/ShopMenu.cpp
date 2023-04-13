#include "ShopMenu.h"
#include "../Engine/Game.h"
#include "../Managers/Player.h"
#include "../Managers/Shop.h"
#include "../Managers/TextureManager.h"
#include "../Objects/SceneObject.h"
#include "Button.h"
#include "UILabel.h"
#include <rapidjson/document.h>

ShopMenu::ShopMenu ()
{
	game = nullptr;
	player = nullptr;
	shop = nullptr;
	renderer = nullptr;
	json = nullptr;
	fullPage = nullptr;
	mainLabel = nullptr;
	playerInfoLabel = nullptr;
	returnButtonLabel = nullptr;
	returnButton = nullptr;
	background = nullptr;
	col_incButton = nullptr;
	col_decButton = nullptr;
	line_incButton = nullptr;
	line_decButton = nullptr;
}

ShopMenu::~ShopMenu ()
{
	line_decButton = nullptr;
	line_incButton = nullptr;
	col_decButton = nullptr;
	col_incButton = nullptr;
	background = nullptr;
	returnButton = nullptr;
	returnButtonLabel = nullptr;
	playerInfoLabel = nullptr;
	mainLabel = nullptr;
	fullPage = nullptr;
	json = nullptr;
	renderer = nullptr;
	shop = nullptr;
	player = nullptr;
	game = nullptr;
}

struct ShopMenu::itemColumn
{
	UILabel label;
	std::deque<LabeledButton> items;

	int
	Pages ()
	{
		return items.size () / 3;
	}
	void
	Render (int begin_column)
	{
		label.Render ();

		int offset = 0;
		if (begin_column + 3 > items.size ())
		{
			offset = begin_column + 3 - items.size ();
		}

		for (auto itr = begin_column; itr < begin_column + 3 - offset; ++itr)
		{
			items[itr].Render ();
		}
	}

	void
	HandleEvents (int begin_column, SDL_Event *event, Shop *shop,
	              bool *bUpdate)
	{
		int offset = 0;
		if (begin_column + 3 > items.size ())
		{
			offset = begin_column + 3 - items.size ();
		}

		for (auto itr = begin_column; itr < begin_column + 3 - offset; ++itr)
		{
			if (items[itr].HandleEvents (event))
			{
				items[itr].button.item (
					shop, (const char *)items[itr].button.GetArg (), (const char *)items[itr].button.GetArg2 ());
				*bUpdate = true;
			}
		}
	}
};

struct ShopMenu::columnLine
{
	std::deque<itemColumn> columns;

	void
	Render (int begin_column, int begin_line)
	{
		int offset = 0;
		if (begin_line + 3 > columns.size ())
		{
			offset = begin_line + 3 - columns.size ();
		}

		for (auto itr = begin_line; itr < begin_line + 3 - offset; ++itr)
		{
			columns[itr].Render (begin_column);
		}
	}

	void
	HandleEvents (int begin_column, int begin_line, SDL_Event *event,
	              Shop *shop, bool *bUpdate)
	{
		int offset = 0;
		if (begin_line + 3 > columns.size ())
		{
			offset = begin_line + 3 - columns.size ();
		}

		for (auto itr = begin_line; itr < begin_line + 3 - offset; ++itr)
		{
			columns[itr].HandleEvents (begin_column, event, shop, bUpdate);
		}
	}
};

struct ShopMenu::Page
{
	columnLine fullPage;

	void
	Render (int begin_column, int begin_line)
	{
		fullPage.Render (begin_column, begin_line);
	}

	void
	HandleEvents (int begin_column, int begin_line, SDL_Event *event,
	              Shop *shop, bool *bUpdate)
	{
		fullPage.HandleEvents (begin_column, begin_line, event, shop, bUpdate);
	}
};

ShopMenu::ShopMenu (SDL_Renderer *renderer, Game *game,
                    TextureManager *textureManager, Player *player,
                    rapidjson::Value *json)
	: ShopMenu::ShopMenu ()
{
	this->game = game;
	this->renderer = renderer;
	this->player = player;
	this->json = json;
	shop = new Shop (player, json);

	background = new SceneObject (
		textureManager->GetTexture ("darkBackground"), renderer);
	playerInfoLabel
		= new UILabel (renderer, 0, 100, FONT_SANS, 32,
	                   ("Fuko: " + std::to_string (player->GetFuko ())),
	                   { 255, 255, 255 }, 1024);
	returnButtonLabel = new UILabel (renderer, 10, 10, FONT_SANS, 32, "Return",
	                                 { 255, 255, 255 }, 150, 100);
	returnButton = new Button (textureManager->GetButtonTexture ("button1"),
	                           { 10, 10, 150, 100 }, renderer,
	                           [] (Game *game) { game->WinMenu (); });
	mainLabel = new UILabel (renderer, 0, 50, FONT_SANS, 48, "Item Shop",
	                         { 255, 255, 255 }, 1024);

	col_incButton
		= new Button (textureManager->GetButtonTexture ("button-arrow-down"),
	                  { 502, 732, 20, 20 }, renderer);
	col_decButton
		= new Button (textureManager->GetButtonTexture ("button-arrow-up"),
	                  { 502, 693, 20, 20 }, renderer);
	line_incButton
		= new Button (textureManager->GetButtonTexture ("button-arrow-right"),
	                  { 522, 713, 20, 20 }, renderer);
	line_decButton
		= new Button (textureManager->GetButtonTexture ("button-arrow-left"),
	                  { 482, 713, 20, 20 }, renderer);

	fullPage = new Page ();

	int tmp_column_counter = 0;
	for (auto &unit : (*json)["items"].GetObject ())
	{

		itemColumn tmp_itemColumn;
		{
			std::string tmp_name = unit.name.GetString ();
			tmp_name[0] = toupper (tmp_name[0]);
			tmp_itemColumn.label = UILabel (
				renderer, 1024 / 3 * tmp_column_counter, 160, FONT_SANS, 24,
				tmp_name, { 255, 255, 255 }, 1024 / 3);
		}

		int tmp_item_counter = 0;
		for (auto &item : unit.value.GetObject ())
		{
			int tmp_offset = 0;
			if (tmp_item_counter % 3 > 0)
				tmp_offset = 40 * (tmp_item_counter % 3);
			SDL_Rect tmp_pos = { (1024 / 3 * tmp_column_counter) + 10,
				                 ((768
				                   - (tmp_itemColumn.label.GetPosition ().y
				                      + tmp_itemColumn.label.GetPosition ().h))
				                  / 3 * (tmp_item_counter % 3))
				                     + tmp_itemColumn.label.GetPosition ().y
				                     + tmp_itemColumn.label.GetPosition ().h
				                     + 20 - tmp_offset,
				                 (1024 / 3) - 20, 150 };
			std::string tmp_text = "";
			std::string tmp_item_name = unit.name.GetString ();
			tmp_item_name.append (item.name.GetString ());
			Item tmp_item = shop->GetItem (tmp_item_name.c_str ());

			tmp_text.append ("\n Cost: " + std::to_string (tmp_item.itemCost));
			tmp_text.append ("\n Level: " + std::to_string (tmp_item.level));
			for (auto &stat : tmp_item.stats)
			{
				auto itr = (*json)["lang"].FindMember (stat.first.c_str ());
				if (itr != (*json)["lang"].MemberEnd ())
				{
					tmp_text.append (
						"\n " + std::string (itr->value.GetString ()) + ": "
						+ std::to_string (stat.second) + " per Level");
				}
			}

			if (tmp_item.drawSpecialEffect)
				for (auto &stat : tmp_item.specialEffectStats)
				{
					auto itr
						= (*json)["lang"].FindMember (stat.first.c_str ());
					if (itr != (*json)["lang"].MemberEnd ())
					{
						tmp_text.append (
							"\n " + std::to_string (stat.second) + " to "
							+ std::string (itr->value.GetString ())
							+ " at level "
							+ std::to_string (tmp_item.specialEffectLevelReq));
					}
				}
			Button tmp_button
				= Button (textureManager->GetButtonTexture ("button1"),
			              tmp_pos, renderer, (void *)item.name.GetString (), (void *)unit.name.GetString (),
			              [] (Shop *shop, const char *itemName, const char *unitClass)
			              { shop->Buy (std::string(unitClass).append(itemName).c_str()); });
			std::string tmp_name = item.name.GetString ();
			tmp_name[0] = toupper (tmp_name[0]);
			UILabel tmp_nameLabel
				= UILabel (renderer, tmp_pos.x, tmp_pos.y + 5, FONT_SANS, 18,
			               tmp_name, { 255, 255, 255 }, tmp_pos.w);
			UILabel tmp_statsLabel
				= UILabel (renderer, tmp_pos.x + 10, tmp_pos.y + 5, FONT_SANS,
			               16, tmp_text, { 255, 255, 255 });

			tmp_itemColumn.items.push_back (
				{ tmp_button,
			      { { "name", tmp_nameLabel },
			        { "stats", tmp_statsLabel } } });

			++tmp_item_counter;
			if (tmp_item_counter > column_count)
				column_count = tmp_item_counter;
		}

		++tmp_column_counter;
		++line_count;
		if (tmp_column_counter == 3)
			tmp_column_counter = 0;

		fullPage->fullPage.columns.push_back (tmp_itemColumn);
	}
}

void
ShopMenu::Reset ()
{
	shop->Reset ();
}

void
ShopMenu::Update (bool bStatUpdate)
{
	playerInfoLabel->ChangeText (
		("Fuko: " + std::to_string (player->GetFuko ())).c_str ());
	if (bStatUpdate)
	{
		for (auto &column : fullPage->fullPage.columns)
		{
			for (auto &button : column.items)
			{
				std::string tmp_text = "";
				auto tmp_item = shop->GetItems ().at (std::string((const char *)button.button.GetArg2 ()).append((const char *)button.button.GetArg ()));

				tmp_text.append ("\n Cost: "
				                 + std::to_string (tmp_item.itemCost));
				tmp_text.append ("\n Level: "
				                 + std::to_string (tmp_item.level));
				for (auto &stat : tmp_item.stats)
				{
					auto itr
						= (*json)["lang"].FindMember (stat.first.c_str ());
					if (itr != (*json)["lang"].MemberEnd ())
					{
						tmp_text.append (
							"\n " + std::string (itr->value.GetString ())
							+ ": " + std::to_string (stat.second)
							+ " per Level");
					}
				}

				if (tmp_item.drawSpecialEffect)
					for (auto &stat : tmp_item.specialEffectStats)
					{
						auto itr
							= (*json)["lang"].FindMember (stat.first.c_str ());
						if (itr != (*json)["lang"].MemberEnd ())
						{
							tmp_text.append (
								"\n " + std::to_string (stat.second) + " to "
								+ std::string (itr->value.GetString ())
								+ " at level "
								+ std::to_string (
									tmp_item.specialEffectLevelReq));
						}
					}

				button.labels.at ("stats").ChangeText (tmp_text.c_str ());
			}
		}
	}
}

void
ShopMenu::Render ()
{
	background->Render ();
	mainLabel->Render ();
	if (begin_column + 3 < column_count)
		col_incButton->Render ();
	if (begin_column - 3 >= 0)
		col_decButton->Render ();
	if (begin_line + 3 < line_count)
		line_incButton->Render ();
	if (begin_line - 3 >= 0)
		line_decButton->Render ();

	fullPage->Render (begin_column, begin_line);
	playerInfoLabel->Render ();
	returnButton->Render ();
	returnButtonLabel->Render ();
}

void
ShopMenu::HandleEvents (SDL_Event *event, bool *bUpdate)
{
	fullPage->HandleEvents (begin_column, begin_line, event, shop, bUpdate);
	if (returnButton->HandleEvents (event))
		returnButton->game (game);

	if (col_incButton->HandleEvents (event) && begin_column + 3 < column_count)
		begin_column += 3;
	if (col_decButton->HandleEvents (event) && begin_column - 3 >= 0)
		begin_column -= 3;
	if (line_incButton->HandleEvents (event) && begin_line + 3 < line_count)
		begin_line += 3;
	if (line_decButton->HandleEvents (event) && begin_line - 3 >= 0)
		begin_line -= 3;
}

void
ShopMenu::Save (rapidjson::Document *saveJson)
{
	shop->Save (saveJson);
}

void
ShopMenu::Load (rapidjson::Value *saveJson)
{
	shop->Load (saveJson);
}