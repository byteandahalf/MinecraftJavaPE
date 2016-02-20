#pragma once

#include "MinecraftJavaItem.h"

struct CarrotOnAStickItem
:public MinecraftJavaItem
{
	CarrotOnAStickItem(short);

	virtual bool isMirroredArt() const;
};
