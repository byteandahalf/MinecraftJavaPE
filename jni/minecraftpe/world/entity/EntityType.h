#pragma once

enum EntityType
{
	ENTITY_PIG = 5900
};

struct EntityClassTree
{
	static bool isInstanceOf(const Entity&, EntityType);
	static bool isPlayer(const Entity&);
};
