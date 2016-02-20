#pragma once

#include "MinecraftJavaBlock.h"

class JukeboxBlock
:public MinecraftJavaBlock
{
public:
	JukeboxBlock(int);

protected:
	virtual const TextureUVCoordinateSet& getTexture(signed char, int);
	virtual bool use(Player&, const BlockPos&);

private:
	TextureUVCoordinateSet jukebox_bottom;
	TextureUVCoordinateSet jukebox_side;
};
