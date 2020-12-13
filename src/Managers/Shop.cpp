#include "Shop.hpp"

Shop::Shop( Player* player, rapidjson::Value* json )
{
    this->player = player;
    this->json = json;

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
    if( player->Buy( items.at( itemName )->itemCost ) )
    {
        bool isValid = true;

        for( auto stat : items.at( itemName )->stats )
        {
            int previousValue = (*json)["summons"][ items.at( itemName )->unit ][ stat.first.c_str() ].GetInt();

            if( previousValue + stat.second <= 0 ) isValid = false;
            else (*json)["summons"][ items.at( itemName )->unit ][ stat.first.c_str() ].SetInt( previousValue + stat.second );

            if( isValid && items.at( itemName )->specialEffect && items.at( itemName )->specialEffectLevelReq - 1 == items.at( itemName )->level )
            {
                previousValue = (*json)["summons"][ items.at( itemName )->unit ][ items.at( itemName )->specialEffectStat.c_str() ].GetInt();
                (*json)["summons"][ items.at( itemName )->unit ][ items.at( itemName )->specialEffectStat.c_str() ].SetInt( previousValue + items.at( itemName )->specialEffectStatIncrese );
                items.at( itemName )->specialEffect = false;
            }
        }

        if( isValid )
            ++items.at( itemName )->level;
    }
}