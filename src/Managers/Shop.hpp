#pragma once
#include "Player.hpp"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "unordered_map"

struct Item
{
    const char* unit;
    int level = 0;
    int itemCost = 0;
    std::unordered_map< std::string, int > stats;

    bool specialEffect = false;
    int specialEffectLevelReq;
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

    Item GetItem( const char* itemName ){ return items.at( itemName ); };
    void IncreaseLevel( const char* itemName ){ ++items.at( itemName ).level; };
    void Buy( const char* itemName );
    void Buy( const char* itemName, rapidjson::Value& json );

    void Save( rapidjson::Document* saveJson );
    void Load( rapidjson::Value* saveJson );
};