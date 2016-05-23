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

/*
*	DANGER ZONE:
*	AWFUL CODE
*	FOR VARIOUS TESTS
*/

static void (*__test)(void*, void*, const std::string&);
static void _test(void* retval, void* self, const std::string& what)
{
	static bool lastPig = false;

	if(lastPig)
	{
		lastPig = false;
		return __test(retval, self, "geometry.cow");
	}

	if(what == "geometry.pig")
	{
		lastPig = true;
	}

	__test(retval, self, what);
}

enum TextureLocation
{
	TEXLOC_ZERO = 0
};

namespace mce
{
	struct RenderContext
	{};

	struct RenderContextImmediate
	{
		static RenderContext& get();
	};

	struct Texture
	{
		void bindTexture(mce::RenderContext&, unsigned int, unsigned int) const;
	};

	struct TexturePtr
	{
		char filler[12];
		TexturePtr();
		mce::Texture* operator->() const;
	};

	struct TextureGroup
	{
		mce::TexturePtr getTexture(const std::string&, TextureLocation);
	};
};

static mce::TexturePtr saddle;

struct PigRenderer
{
	char filler[148];
	mce::TexturePtr texture;
};

static int _renderPigArmor(PigRenderer* self)
{
	saddle->bindTexture(mce::RenderContextImmediate::get(), 1, 2);
	return 1;
}

static void* (*__ctor)(void*, mce::TextureGroup&, void*, void*, float);
static void* _ctor(void* self, mce::TextureGroup& group, void* geo, void* geo2, float f)
{
	saddle = group.getTexture("mob/saddle.png", TEXLOC_ZERO);
	return __ctor(self, group, geo, geo2, f);
}


/* Use a handle for hooking constructors/overloaded functions */
static void initHooks(void* _minecraftpe)
{
	void* test = (void*) dlsym(_minecraftpe, "_ZN13GeometryGroup11getGeometryERKSs");
	MSHookFunction(test, (void*) &_test, (void**) &__test);
	void* ctor = (void*) dlsym(_minecraftpe, "_ZN11PigRendererC2ERN3mce12TextureGroupERK11GeometryPtrS5_f");
	MSHookFunction(ctor, (void*) &_ctor, (void**) &__ctor);
	uintptr_t** pigrender_vt = (uintptr_t**) dlsym(_minecraftpe, "_ZTV11PigRenderer");
	pigrender_vt[7] = (uintptr_t*) &_renderPigArmor;


	MSHookFunction((void*) &Minecraft::init, (void*) &Minecraft$init, (void**) &_Minecraft$init);

	MinecraftHook::initHooks(_minecraftpe);
}

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
	initHooks(dlopen("libminecraftpe.so", RTLD_LAZY));
	return JNI_VERSION_1_2;
}
