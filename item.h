#ifndef ITEM_H
#define ITEM_H
//道具实体：金币、血瓶
#include "entity.h"
enum itemType{
    ITEM_COIN,
    ITEM_HP
};

class Item:public entity
{
public:
    Item();
    itemType type;
};

#endif // ITEM_H
