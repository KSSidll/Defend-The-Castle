#ifndef MANAGERS_SHOP_H_
#define MANAGERS_SHOP_H_

#include <rapidjson/fwd.h>
#include <string>
#include <unordered_map>

class Player;

struct Item
{
	const char *unit;
	int level = 0;
	int itemCost = 0;
	std::unordered_map<std::string, int> stats;

	bool drawSpecialEffect = false;
	bool bSpecialEffectSet = false;
	int specialEffectLevelReq = -1;
	std::unordered_map<std::string, int> specialEffectStats;
};

class Shop
{
  private:
	rapidjson::Value *json;
	Player *player;

	std::unordered_map<std::string, Item> items;

  public:
	Shop ();
	~Shop ();

	Shop (Player *player, rapidjson::Value *json);

	void Reset ();

	void IncreaseLevel (const char *itemName);
	void Buy (const char *itemName);

	void Save (rapidjson::Document *saveJson);
	void Load (rapidjson::Value *saveJson);

	Item GetItem (const char *key);
	std::unordered_map<std::string, Item> GetItems ();
};

#endif // MANAGERS_SHOP_H_