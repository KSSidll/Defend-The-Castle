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
    items.insert({ "spear", spear });

    Item* armor = new Item();
    armor->stats.insert({ "health", 15 });
    armor->stats.insert({ "movementSpeed", -1 });
    items.insert({ "armor", armor });

    Item* bow = new Item();
    bow->stats.insert({ "attackDamage", 2 });
    bow->stats.insert({ "attackSpeed", -1 });
    bow->specialEffect = true;
    bow->specialEffectLevelReq = 5;
    bow->specialEffectStat = "cost";
    bow->specialEffectStatIncrese = -1;
    items.insert({ "bow", bow });
}