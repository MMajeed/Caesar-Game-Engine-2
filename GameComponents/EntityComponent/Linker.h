#ifndef __ENTITYCOMPONENT_GUARD_linklib__
#define __ENTITYCOMPONENT_GUARD_linklib__

#if defined(_DEBUG)
	#pragma comment (lib,"EntityComponent-mt-d.lib")
#elif !defined(_DEBUG)
	#pragma comment (lib,"EntityComponent-mt.lib")
#else
	#error link: no suitable library
#endif

#endif // __ENTITYCOMPONENT_GUARD_linklib__