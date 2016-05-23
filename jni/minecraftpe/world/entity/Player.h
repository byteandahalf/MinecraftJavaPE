#pragma once

#include "Mob.h"
struct Player
: public Mob
{
	const ItemInstance& getSelectedItem() const;
};
