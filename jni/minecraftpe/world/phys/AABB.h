#pragma once

#include "Vec3.h"

struct AABB
{
	Vec3 min, max;
	bool _empty;
};
