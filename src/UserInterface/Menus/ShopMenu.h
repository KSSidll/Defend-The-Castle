#ifndef USER_INTERFACE_SHOP_MENU_H_
#define USER_INTERFACE_SHOP_MENU_H_

#include "../../Game.h"
#include "../../Managers/FontManager.h"
#include "../../Managers/Shop.h"
#include "../../Objects/SceneObject.h"
#include "../Components/Button.h"
#include "../Components/ShopPage.h"
#include "../Components/UILabel.h"
#include <deque>

class ShopMenu
{
  private:
	Player *player;
	Shop *shop;
	rapidjson::Value *json;

	int begin_column = 0;
	int begin_line = 0;

	int column_count = 0;
	int line_count = 0;

	ShopPage fullPage;

	UILabel mainLabel;
	UILabel playerInfoLabel;
	UILabel returnButtonLabel;
	Button returnButton;
	SceneObject background;

	Button col_incButton;
	Button col_decButton;
	Button line_incButton;
	Button line_decButton;

	void UpdateItemsStats ();

  public:
	ShopMenu ();
	~ShopMenu ();

	ShopMenu (SDL_Renderer *renderer, TextureManager *textureManager,
	          FontManager *fontManager, Game *game, Player *player,
	          rapidjson::Value *json);

	void Reset ();

	void Update (bool bStatUpdate = false);
	void Render () const;
	void HandleEvents (SDL_Event *event, bool *bUpdate);
	void Save (rapidjson::Document *saveJson) const;
	void Load (const rapidjson::Value *saveJson);
};

#endif // USER_INTERFACE_SHOP_MENU_H_