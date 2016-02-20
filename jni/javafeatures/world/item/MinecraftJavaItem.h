#pragma once

#include "minecraftpe/world/item/Item.h"

struct MinecraftJavaItem
: public Item
{
	static Item* carrot_on_a_stick;

	MinecraftJavaItem(const std::string&, short);

	static Item* registerItem(Item**, Item*);
};
