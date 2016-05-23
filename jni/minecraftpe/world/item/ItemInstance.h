#pragma once

struct Item;
struct Block;
struct CompoundTag;

struct ItemInstance
{
	short count, auxData; // 0, 2
	CompoundTag* userData; // 4
	Block* block; // 8
	Item* item; // 12
};
