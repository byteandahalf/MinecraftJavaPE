#include "minecraftpe/world/material/Material.h"

#include "JukeboxBlock.h"

JukeboxBlock::JukeboxBlock(int blockId)
	:MinecraftJavaBlock("jukebox", blockId, Material::getMaterial(MaterialType::WOOD)){

	texture = getTextureUVCoordinateSet("jukebox_top", 0);
	jukebox_bottom = getTextureUVCoordinateSet("noteblock", 0);
	jukebox_side = getTextureUVCoordinateSet("jukebox_side", 0);
}

const TextureUVCoordinateSet& JukeboxBlock::getTexture(signed char side, int metadata)
{
	return (side == 0)? jukebox_bottom : ((side == 1)? texture : jukebox_side);
}

bool JukeboxBlock::use(Player& localPlayer, const BlockPos& worldPos)
{
	/* insert disc */
	return false;
}
