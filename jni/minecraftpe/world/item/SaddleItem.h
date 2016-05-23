#pragma once

#include "Item.h"
class SaddleItem
: public Item
{
	virtual ~SaddleItem();
	virtual void hurtEnemy(ItemInstance*, Mob*, Mob*);
	virtual void interactEnemy(ItemInstance*, Mob*, Player*);
};
