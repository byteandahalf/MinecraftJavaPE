#include <dlfcn.h>

#include "minecraftpe/world/entity/Player.h"
#include "minecraftpe/world/entity/EntityType.h"
#include "minecraftpe/world/level/BlockSource.h"
#include "minecraftpe/world/level/Level.h"
#include "minecraftpe/world/item/Item.h"
#include "minecraftpe/world/item/ItemInstance.h"

/* main */
#include "MinecraftHook.h"
void MinecraftHook::initHooks(void* _minecraftpe)
{
	MinecraftHook::Pig::initHooks(_minecraftpe);
	MinecraftHook::SaddleItem::initHooks(_minecraftpe);
}

/*
*	Pig
*/
#include "minecraftpe/world/entity/Pig.h"
uintptr_t** MinecraftHook::Pig::VTABLE;
void MinecraftHook::Pig::initHooks(void* _minecraftpe)
{
	VTABLE = (uintptr_t**)(((uintptr_t)dlsym(_minecraftpe, "_ZTV3Pig")) + 8);

	_interactWithPlayer = (bool (*)(::Pig*, Player&)) VTABLE[50];
	VTABLE[50] = (uintptr_t*) &interactWithPlayer;
	VTABLE[51] = (uintptr_t*) &canInteractWith;
	_getInteractText = (std::string (*)(::Pig*, Player&)) VTABLE[52];
	VTABLE[52] = (uintptr_t*) &getInteractText;
	VTABLE[99] = (uintptr_t*) &canAddRider;
}

bool (*MinecraftHook::Pig::_interactWithPlayer)(::Pig*, Player&);
bool MinecraftHook::Pig::interactWithPlayer(::Pig* self, Player& player)
{
	if(_interactWithPlayer(self, player))
	{
		return true;
	}
	if(self->hasSaddle())
	{
		if(!player.region.getLevel()->isClientSide())
		{
			/* TODO: too lazy to setup vtables */
			uintptr_t** vtable = *((uintptr_t***) &player);
			void (*ride)(Player*, Entity&) = (void (*)(Player*, Entity&)) vtable[104/4];
			ride(&player, *self);
			return true;
		}
	}
	return false;
}

bool MinecraftHook::Pig::canInteractWith(::Pig* self, Player& player)
{
	if(player.getSelectedItem().item == Item::mSaddle && !self->hasSaddle())
	{
		return true;
	}
	return false;
}

std::string (*MinecraftHook::Pig::_getInteractText)(::Pig*, Player&);
std::string MinecraftHook::Pig::getInteractText(::Pig* self, Player& player)
{
	if(player.getSelectedItem().item == Item::mSaddle)
	{
		return "Mount";
	}

	return _getInteractText(self, player);
}

bool MinecraftHook::Pig::canAddRider(::Pig* self, Entity& entity)
{
	return EntityClassTree::isPlayer(entity);
}

/*
*	SaddleItem
*/
#include "minecraftpe/world/item/SaddleItem.h"
uintptr_t** MinecraftHook::SaddleItem::VTABLE;
void MinecraftHook::SaddleItem::initHooks(void* _minecraftpe)
{
	/* TODO: SaddleItem vtable */
	VTABLE = (uintptr_t**)(((uintptr_t)dlsym(_minecraftpe, "_ZTV10SaddleItem")) + 8);

	VTABLE[38] = (uintptr_t*) &interactEnemy;
}

bool MinecraftHook::SaddleItem::interactEnemy(::SaddleItem* self, ItemInstance* itemStack, Mob* enemy, Player* player)
{
	if(EntityClassTree::isInstanceOf(*enemy, EntityType::ENTITY_PIG))
	{
		::Pig* pig = (::Pig*) enemy;
		if(!pig->hasSaddle() && !pig->isBaby())
		{
			pig->setSaddle(true);
			return true;
		}
	}

	return false;
}
