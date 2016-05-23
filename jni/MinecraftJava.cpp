#include <jni.h>
#include <dlfcn.h>
#include <android/log.h>
#include <stdlib.h>
#include <substrate.h>

#include "javafeatures/hooks/MinecraftHook.h"
#include "javafeatures/world/item/MinecraftJavaItem.h"
#include "javafeatures/world/item/CarrotOnAStickItem.h"
#include "javafeatures/world/level/block/MinecraftJavaBlock.h"
#include "javafeatures/world/level/block/JukeboxBlock.h"

#include "minecraftpe/world/item/Item.h"
#include "minecraftpe/client/game/Minecraft.h"

static void initCustomItems()
{
	MinecraftJavaItem::registerItem(&MinecraftJavaItem::carrot_on_a_stick, new CarrotOnAStickItem(398));
}

static void initBlockItems()
{
	
}

static void initCustomBlocks()
{
	MinecraftJavaBlock::registerBlock(&MinecraftJavaBlock::jukebox, new JukeboxBlock(84));
}

static void initCreativeItems()
{
	Item::addCreativeItem(MinecraftJavaItem::carrot_on_a_stick, 0);
}


static void (*_Minecraft$init)(Minecraft*, const std::string&);
static void Minecraft$init(Minecraft* self, const std::string& s)
{
	_Minecraft$init(self, s);

	initCustomItems();
	initCustomBlocks();
	initBlockItems();
	initCreativeItems();
}

/* Use a handle for hooking constructors/overloaded functions */
static void initHooks(void* _minecraftpe)
{
	MSHookFunction((void*) &Minecraft::init, (void*) &Minecraft$init, (void**) &_Minecraft$init);

	MinecraftHook::initHooks(_minecraftpe);
}

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
	initHooks(dlopen("libminecraftpe.so", RTLD_LAZY));
	return JNI_VERSION_1_2;
}
