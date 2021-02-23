#define RAPIDJSON_HAS_STDSTRING 1
#include "Shop.hpp"
#include "Player.hpp"

Shop::Shop()
{
    this->json = nullptr;
    this->player = nullptr;
}

Shop::~Shop()
{
    this->player = nullptr;
    this->json = nullptr;
}

Shop::Shop( Player* player, rapidjson::Value* json )
{
    this->json = json;
    this->player = player;

    for( auto& unit : (*json)["items"].GetObject() )
    {
        for( auto& itemData : unit.value.GetObject() )
        {
            Item tmp_item;
            tmp_item.itemCost = itemData.value["itemCost"].GetInt();
            tmp_item.unit = unit.name.GetString();
            for( auto& stat : itemData.value["stats"].GetObject() )
            {
                tmp_item.stats.emplace( stat.name.GetString(), stat.value.GetInt() );
            }

            auto itr = itemData.value.FindMember("specialEffect");
            if( itr != itemData.value.MemberEnd() )
            {
                tmp_item.specialEffect = true;
                tmp_item.specialEffectLevelReq = itr->value["levelReq"].GetInt();
                for( auto& stat : itr->value["stats"].GetObject() )
                {
                    tmp_item.specialEffectStats.emplace( stat.name.GetString(), stat.value.GetInt() );
                }
            }
            items.emplace( itemData.name.GetString(), tmp_item );
        }
    }
}

void Shop::Reset()
{
    for( auto& item: items )
    {
        item.second.level = 0;
    }
}

void Shop::Buy( const char* itemName )
{
    if( player->Buy( items.at( itemName ).itemCost ) )
    {
        bool isValid = true;

        for( auto stat : items.at( itemName ).stats )
        {
            int previousValue = (*json)["summons"][ items.at( itemName ).unit ][ stat.first.c_str() ].GetInt();

            if( previousValue + stat.second <= 0 ) isValid = false;
            else (*json)["summons"][ items.at( itemName ).unit ][ stat.first.c_str() ].SetInt( previousValue + stat.second );

            if( isValid && items.at( itemName ).specialEffect && items.at( itemName ).specialEffectLevelReq - 1 == items.at( itemName ).level )
            {
                for( auto& stat : items.at( itemName ).specialEffectStats )
                {
                    previousValue = (*json)["summons"][ items.at( itemName ).unit ][ stat.first.c_str() ].GetInt();
                    (*json)["summons"][ items.at( itemName ).unit ][ stat.first.c_str() ].SetInt( previousValue + stat.second );
                    items.at( itemName ).specialEffect = false;
                }
            }
        }

        if( isValid )
            ++items.at( itemName ).level;
        else player->ReturnFuko( items.at( itemName ).itemCost );
    }
}

void Shop::Save( rapidjson::Document* saveJson )
{
    rapidjson::Value object( rapidjson::kObjectType );

    for( auto& item : items )
    {
        object.AddMember( rapidjson::Value(item.first + "Level", saveJson->GetAllocator()).Move(), item.second.level, saveJson->GetAllocator() );
    }

    saveJson->AddMember( "shop", object, saveJson->GetAllocator() );
}

void Shop::Load( rapidjson::Value* saveJson )
{
    for( auto& item : items)
    {
        if( (*saveJson)["shop"].HasMember(item.first + "Level") )
        for( int it = 0; it < (*saveJson)["shop"][item.first + "Level"].GetInt(); ++it )
        {
            bool isValid = true;
            for( auto& stat : item.second.stats)
            {
                int previousValue = (*json)["summons"][ item.second.unit ][ stat.first.c_str() ].GetInt();
                if( previousValue + stat.second <= 0 ) isValid = false;
                else (*json)["summons"][item.second.unit][ stat.first.c_str() ].SetInt( previousValue + stat.second );

                if( isValid && item.second.specialEffect && item.second.specialEffectLevelReq - 1 == item.second.level )
                {
                    for( auto& stat : items.at( item.first ).specialEffectStats )
                    {
                        previousValue = (*json)["summons"][ items.at( item.first ).unit ][ stat.first.c_str() ].GetInt();
                        (*json)["summons"][ items.at( item.first ).unit ][ stat.first.c_str() ].SetInt( previousValue + stat.second );
                        items.at( item.first ).specialEffect = false;
                    }
                }
            }
            if( isValid )
                ++item.second.level;
            else break;
        }
    }
}