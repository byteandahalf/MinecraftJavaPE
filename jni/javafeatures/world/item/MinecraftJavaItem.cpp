
#include "MinecraftJavaItem.h"

Item* MinecraftJavaItem::carrot_on_a_stick;

MinecraftJavaItem::MinecraftJavaItem(const std::string& name, short itemId)
	:Item(name, itemId - 0x100) {
	setIcon(name, 0);
}


Item* MinecraftJavaItem::registerItem(Item** ptr, Item* item)
{
	mItems[item->itemId] = item;
	*ptr = item;
	return item;
}