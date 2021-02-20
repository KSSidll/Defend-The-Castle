#define RAPIDJSON_HAS_STDSTRING 1
#include "Shop.hpp"

Shop::Shop( Player* player, rapidjson::Value* json )
{
    this->player = player;
    this->json = json;

    Item* spear = new Item();
    spear->itemCost = 3;
    spear->unit = "warrior";
    spear->stats.insert({ "attackDamage", 1 });
    spear->stats.insert({ "attackSpeed", -1 });
    spear->specialEffect = true;
    spear->specialEffectLevelReq = 5;
    spear->specialEffectStat = "range";
    spear->specialEffectStatIncrese = 50;
    items.insert({ "spear", spear });

    Item* armor = new Item();
    armor->itemCost = 4;
    armor->unit = "tank";
    armor->stats.insert({ "health", 15 });
    armor->stats.insert({ "movementSpeed", -1 });
    items.insert({ "armor", armor });

    Item* bow = new Item();
    bow->itemCost = 5;
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
        else player->ReturnFuko( items.at( itemName )->itemCost );
    }
}

void Shop::Save( rapidjson::Document* saveJson )
{
    rapidjson::Value object( rapidjson::kObjectType );

    for( auto& item : items )
    {
        object.AddMember( rapidjson::Value(item.first + "Level", saveJson->GetAllocator()).Move(), item.second->level, saveJson->GetAllocator() );
    }

    saveJson->AddMember( "shop", object, saveJson->GetAllocator() );
}

void Shop::Load( rapidjson::Value* saveJson )
{
    // std::unordered_map< std::string, int > levels;
    // for( auto& item : items)
    // {
    //     levels.emplace( item.first, (*saveJson)["shop"][item.first + "level"].GetInt() );
    // }

    //
    for( auto& item : items)
    {
        for( int it = 0; it < (*saveJson)["shop"][item.first + "Level"].GetInt(); ++it)
        {
            bool isValid = true;
            for( auto& stat : item.second->stats)
            {
                int previousValue = (*json)["summons"][ item.second->unit ][ stat.first.c_str() ].GetInt();
                if( previousValue + stat.second <= 0 ) isValid = false;
                else (*json)["summons"][item.second->unit][ stat.first.c_str() ].SetInt( previousValue + stat.second );

                if( isValid && item.second->specialEffect && item.second->specialEffectLevelReq - 1 == item.second->level )
                {
                    previousValue = (*json)["summons"][item.second->unit][ item.second->specialEffectStat.c_str() ].GetInt();
                    (*json)["summons"][item.second->unit][ item.second->specialEffectStat.c_str() ].SetInt( previousValue + item.second->specialEffectStatIncrese );
                    item.second->specialEffect = false;
                }
            }
            if( isValid )
                ++item.second->level;
            else break;
        }
    }
    //

    // for( auto& item : levels )
    // {
    //     for( int it = 0; it < item.second; ++it )
    //     {
    //         bool isValid = true;
    //         for( auto stat : items.at( item.first )->stats )
    //         {
    //             int previousValue = (*json)["summons"][ items.at( item.first )->unit ][ stat.first.c_str() ].GetInt();

    //             if( previousValue + stat.second <= 0 ) isValid = false;
    //             else (*json)["summons"][ items.at( item.first )->unit ][ stat.first.c_str() ].SetInt( previousValue + stat.second );

    //             if( isValid && items.at( item.first )->specialEffect && items.at( item.first )->specialEffectLevelReq - 1 == items.at( item.first )->level )
    //             {
    //                 previousValue = (*json)["summons"][ items.at( item.first )->unit ][ items.at( item.first )->specialEffectStat.c_str() ].GetInt();
    //                 (*json)["summons"][ items.at( item.first )->unit ][ items.at( item.first )->specialEffectStat.c_str() ].SetInt( previousValue + items.at( item.first )->specialEffectStatIncrese );
    //                 items.at( item.first )->specialEffect = false;
    //             }
    //         }
    //         if( isValid )
    //             ++items.at( item.first )->level;
    //         else break;
    //     }
    // }
}