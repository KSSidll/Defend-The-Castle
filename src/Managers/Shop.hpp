#pragma once
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include <bits/stdc++.h>

struct Item
{
    int level = 0;
    int itemCost = 0;

    std::map< std::string, int > stats;

    bool specialEffect = false;
    int specialEffectLevelReq;
    std::string specialEffectStat;
    int specialEffectStatIncrese;
};

class Shop
{
private:
    std::map< std::string, Item* > items;

public:
    Shop();
    ~Shop(){};

    Item* GetItem( const char* itemName ){ return items.at( itemName ); };
};