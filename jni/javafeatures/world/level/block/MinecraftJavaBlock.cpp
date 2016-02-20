
#include "MinecraftJavaBlock.h"

Block* MinecraftJavaBlock::jukebox;

MinecraftJavaBlock::MinecraftJavaBlock(const std::string& name, int blockId, const Material& material)
	:Block("minecraftjava." + name, blockId, material) {

	init();
}

Block* MinecraftJavaBlock::registerBlock(Block** ptr, Block* block)
{
	mBlocks[block->blockId] = block;
	*ptr = block;
	return block;
}
