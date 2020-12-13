#include "Shop.hpp"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"

Shop::Shop( Player* player, rapidjson::Value& json )
{
    this->player = player;
    this->json = &json;

    Item* spear = new Item();
    spear->unit = "warrior";
    spear->stats.insert({ "attackDamage", 1 });
    spear->stats.insert({ "attackSpeed", -1 });
    spear->specialEffect = true;
    spear->specialEffectLevelReq = 5;
    spear->specialEffectStat = "range";
    spear->specialEffectStatIncrese = 50;
    items.insert({ "spear", spear });

    Item* armor = new Item();
    armor->unit = "tank";
    armor->stats.insert({ "health", 15 });
    armor->stats.insert({ "movementSpeed", -1 });
    items.insert({ "armor", armor });

    Item* bow = new Item();
    bow->unit = "archer";
    bow->stats.insert({ "attackDamage", 2 });
    bow->stats.insert({ "attackSpeed", -1 });
    bow->specialEffect = true;
    bow->specialEffectLevelReq = 5;
    bow->specialEffectStat = "cost";
    bow->specialEffectStatIncrese = -1;
    items.insert({ "bow", bow });
}

void Shop::Buy( const char* itemName )
{
    rapidjson::Value& test = *json;
    if( player->Buy( items.at( itemName )->itemCost ) )
    {
        for( auto stat : items.at( itemName )->stats )
        {
            auto statb = test["summons"]["warrior"]["cost"].GetInt();
            //auto stata = test["summons"][ items.at( itemName )->unit ][ *stat.first.c_str() ].SetInt( stat.second );
        }

        ++items.at( itemName )->level;
    }
}
