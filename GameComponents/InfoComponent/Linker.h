#ifndef __INFOCOMPONENT_GUARD_linklib__
#define __INFOCOMPONENT_GUARD_linklib__

#if defined(_DEBUG)
	#pragma comment (lib,"InfoComponent-mt-d.lib")
#elif !defined(_DEBUG)
	#pragma comment (lib,"InfoComponent-mt.lib")
#else
	#error link: no suitable library
#endif

#endif // __INFOCOMPONENT_GUARD_linklib__