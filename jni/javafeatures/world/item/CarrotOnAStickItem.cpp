
#include "CarrotOnAStickItem.h"

CarrotOnAStickItem::CarrotOnAStickItem(short itemId)
	:MinecraftJavaItem("carrot_on_a_stick", itemId) {

	setMaxStackSize(1);
	setMaxDamage(25);
}

bool CarrotOnAStickItem::isMirroredArt() const
{
	return true;
}