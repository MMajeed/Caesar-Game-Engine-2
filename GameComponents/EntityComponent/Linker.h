#ifndef __ENTITYCOMPONENT_GUARD_linklib__
#define __ENTITYCOMPONENT_GUARD_linklib__

#if defined(_DEBUG)
#pragma comment (lib,"EntityComponent-mt-d.lib")
#elif defined(NDEBUGNO)
#pragma comment (lib,"EntityComponent-mt-no.lib")
#elif defined(NDEBUG)
#pragma comment (lib,"EntityComponent-mt.lib")
#else
	#error link: no suitable library
#endif

#endif // __ENTITYCOMPONENT_GUARD_linklib__