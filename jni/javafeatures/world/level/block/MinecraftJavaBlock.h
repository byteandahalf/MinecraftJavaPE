#pragma once

#include "minecraftpe/world/level/block/Block.h"

struct MinecraftJavaBlock
:public Block
{
	static Block* jukebox;

	MinecraftJavaBlock(const std::string&, int, const Material&);

	static Block* registerBlock(Block**, Block*);
};
