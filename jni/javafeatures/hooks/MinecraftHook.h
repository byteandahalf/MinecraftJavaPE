#pragma once

struct ItemInstance;
class Mob;
class Player;
struct Entity;

class Pig;
class SaddleItem;

#include <cstdint>
#include <string>

namespace MinecraftHook
{
	void initHooks(void*);

	/* Pig */
	struct Pig
	{
		static uintptr_t** VTABLE;
		static void initHooks(void*);

		static bool (*_interactWithPlayer)(::Pig*, Player&);
		static bool interactWithPlayer(::Pig*, Player&);

		static bool canInteractWith(::Pig*, Player&);

		static std::string (*_getInteractText)(::Pig*, Player&);
		static std::string getInteractText(::Pig*, Player&);

		static bool canAddRider(::Pig*, Entity&);
	};

	/* SaddleItem */
	struct SaddleItem
	{
		static uintptr_t** VTABLE;
		static void initHooks(void*);

		static bool interactEnemy(::SaddleItem*, ItemInstance*, Mob*, Player*);
	};
};
