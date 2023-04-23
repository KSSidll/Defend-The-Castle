#include "ShopMenu.h"
#include "../../Managers/Player.h"
#include "../../Managers/TextureManager.h"
#include "../UserInterface.h"

ShopMenu::ShopMenu ()
{
	player = nullptr;
	shop = nullptr;
	json = nullptr;
}

ShopMenu::~ShopMenu ()
{
	json = nullptr;
	if (shop)
		delete shop;
	player = nullptr;
}

ShopMenu::ShopMenu (SDL_Renderer *renderer, TextureManager *textureManager,
                    FontManager *fontManager, UserInterface *userInterface,
                    Player *player, rapidjson::Value *json)
{
	this->player = player;
	shop = new Shop (player, json);
	this->json = json;

	background = SceneObject (renderer,
	                          textureManager->GetTexture ("darkBackground"));
	playerInfoLabel
		= UILabel (renderer, 0, 100, fontManager->GetFont (FONT_SANS, 32),
	               ("Fuko: " + std::to_string (player->GetFuko ())),
	               { 255, 255, 255 }, 1024);
	returnButtonLabel
		= UILabel (renderer, 10, 10, fontManager->GetFont (FONT_SANS, 32),
	               "Return", { 255, 255, 255 }, 150, 100);
	returnButton
		= Button (renderer, textureManager->GetButtonTexture ("button1"),
	              { 10, 10, 150, 100 },
	              [this, userInterface]
	              {
					  userInterface->EnableWinMenu ();
					  this->enabled = false;
				  });
	mainLabel = UILabel (renderer, 0, 50, fontManager->GetFont (FONT_SANS, 48),
	                     "Item Shop", { 255, 255, 255 }, 1024);

	col_incButton = Button (
		renderer, textureManager->GetButtonTexture ("button-arrow-down"),
		{ 502, 732, 20, 20 });
	col_decButton = Button (
		renderer, textureManager->GetButtonTexture ("button-arrow-up"),
		{ 502, 693, 20, 20 });
	line_incButton = Button (
		renderer, textureManager->GetButtonTexture ("button-arrow-right"),
		{ 522, 713, 20, 20 });
	line_decButton = Button (
		renderer, textureManager->GetButtonTexture ("button-arrow-left"),
		{ 482, 713, 20, 20 });

	fullPage = ShopPage ();

	int tmp_column_counter = 0;
	for (const auto &unit : (*json)["items"].GetObject ())
	{

		itemColumn tmp_itemColumn;
		{
			std::string tmp_name = unit.name.GetString ();
			tmp_name[0] = toupper (tmp_name[0]);
			tmp_itemColumn.label
				= UILabel (renderer, 1024 / 3 * tmp_column_counter, 160,
			               fontManager->GetFont (FONT_SANS, 24), tmp_name,
			               { 255, 255, 255 }, 1024 / 3);
		}

		int tmp_item_counter = 0;
		for (const auto &item : unit.value.GetObject ())
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
			for (const auto &stat : tmp_item.stats)
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
				for (const auto &stat : tmp_item.specialEffectStats)
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
			Button tmp_button = Button (
				renderer, textureManager->GetButtonTexture ("button1"),
				tmp_pos,
				[shop = shop, itemName = item.name.GetString (),
			     unitClass = unit.name.GetString ()] {
					shop->Buy (
						std::string (unitClass).append (itemName).c_str ());
				});
			std::string tmp_name = item.name.GetString ();
			tmp_name[0] = toupper (tmp_name[0]);
			UILabel tmp_nameLabel
				= UILabel (renderer, tmp_pos.x, tmp_pos.y + 5,
			               fontManager->GetFont (FONT_SANS, 18), tmp_name,
			               { 255, 255, 255 }, tmp_pos.w);
			UILabel tmp_statsLabel
				= UILabel (renderer, tmp_pos.x + 10, tmp_pos.y + 5,
			               fontManager->GetFont (FONT_SANS, 16), tmp_text,
			               { 255, 255, 255 });

			tmp_itemColumn.items.push_back (
				{ { tmp_button,
			        { { "name", tmp_nameLabel },
			          { "stats", tmp_statsLabel } } },
			      tmp_item_name });

			++tmp_item_counter;
			if (tmp_item_counter > column_count)
				column_count = tmp_item_counter;
		}

		++tmp_column_counter;
		++line_count;
		if (tmp_column_counter == 3)
			tmp_column_counter = 0;

		fullPage.fullPage.columns.push_back (tmp_itemColumn);
	}
}

void
ShopMenu::Reset ()
{
	shop->Reset ();
}

void
ShopMenu::Update ()
{
	if (!enabled)
		return;

	playerInfoLabel.ChangeText (
		("Fuko: " + std::to_string (player->GetFuko ())).c_str ());
}

void
ShopMenu::UpdateItemsStats ()
{
	for (auto &column : fullPage.fullPage.columns)
	{
		for (auto &button : column.items)
		{
			std::string tmp_text = "";
			auto tmp_item = shop->GetItems ().at (button.item_name);

			tmp_text.append ("\n Cost: " + std::to_string (tmp_item.itemCost));
			tmp_text.append ("\n Level: " + std::to_string (tmp_item.level));
			for (const auto &stat : tmp_item.stats)
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
				for (const auto &stat : tmp_item.specialEffectStats)
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

			button.button.labels.at ("stats").ChangeText (tmp_text.c_str ());
		}
	}
}

void
ShopMenu::Render () const
{
	if (!enabled)
		return;

	background.Render ();
	mainLabel.Render ();
	if (begin_column + 3 < column_count)
		col_incButton.Render ();
	if (begin_column - 3 >= 0)
		col_decButton.Render ();
	if (begin_line + 3 < line_count)
		line_incButton.Render ();
	if (begin_line - 3 >= 0)
		line_decButton.Render ();

	fullPage.Render (begin_column, begin_line);
	playerInfoLabel.Render ();
	returnButton.Render ();
	returnButtonLabel.Render ();
}
void
ShopMenu::HandleEvents (SDL_Event *event, bool *bUpdate)
{
	if (!enabled)
		return;

	fullPage.HandleEvents (begin_column, begin_line, event, bUpdate);
	returnButton.HandleEvents (event, true);

	if (col_incButton.HandleEvents (event) && begin_column + 3 < column_count)
		begin_column += 3;
	if (col_decButton.HandleEvents (event) && begin_column - 3 >= 0)
		begin_column -= 3;
	if (line_incButton.HandleEvents (event) && begin_line + 3 < line_count)
		begin_line += 3;
	if (line_decButton.HandleEvents (event) && begin_line - 3 >= 0)
		begin_line -= 3;
}

void
ShopMenu::Save (rapidjson::Document *saveJson) const
{
	shop->Save (saveJson);
}

void
ShopMenu::Load (const rapidjson::Value *saveJson)
{
	shop->Load (saveJson);
}

void
ShopMenu::Enable ()
{
	enabled = true;
}

bool
ShopMenu::IsEnabled () const
{
	return enabled;
}