#pragma once
#include "rapidjson/document.h"
#include "unordered_map"

class Player;

struct Item
{
    const char* unit;
    int level = 0;
    int itemCost = 0;
    std::unordered_map< std::string, int > stats;

    bool drawSpecialEffect = false;
    bool bSpecialEffectSet = false;
    int specialEffectLevelReq = -1;
    std::unordered_map< std::string, int > specialEffectStats;
};

class Shop
{
private:
    rapidjson::Value* json;
    Player* player;
    
    std::unordered_map< std::string, Item > items;

public:
    Shop();
    ~Shop();

    Shop( Player* player, rapidjson::Value* json );

    Item GetItem( const char* key ){ return items.at(key); };
    std::unordered_map< std::string, Item > GetItems(){ return items; };

    void Reset();

    void IncreaseLevel( const char* itemName ){ ++items.at( itemName ).level; };
    void Buy( const char* itemName );
    void Buy( const char* itemName, rapidjson::Value& json );

    void Save( rapidjson::Document* saveJson );
    void Load( rapidjson::Value* saveJson );
};