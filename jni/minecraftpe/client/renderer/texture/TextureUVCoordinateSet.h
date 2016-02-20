#pragma once

struct TextureUVCoordinateSet
{
	float minU, minV;
	float maxU, maxV;
	unsigned short _w, _h; 
	int index, textureFile;
};
