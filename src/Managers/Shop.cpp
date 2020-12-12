#include "Shop.hpp"

Shop::Shop()
{
    Item* spear = new Item();
    spear->stats.insert({ "attackDamage", 1 });
    spear->stats.insert({ "attackSpeed", -1 });
    spear->specialEffect = true;
    spear->specialEffectLevelReq = 5;
    spear->specialEffectStat = "range";
    spear->specialEffectStatIncrese = 50;
    items.insert({ "Spear", spear });
}