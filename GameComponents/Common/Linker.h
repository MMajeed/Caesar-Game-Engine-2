#ifndef __COMMON_GUARD_linklib__
#define __COMMON_GUARD_linklib__

#if defined(_DEBUG)
#pragma comment (lib,"Common-mt-d.lib")
#elif defined(NDEBUGNO)
#pragma comment (lib,"Common-mt-no.lib")
#elif defined(NDEBUG)
#pragma comment (lib,"Common-mt.lib")
#else
	#error link: no suitable library
#endif

#endif // __COMMON_GUARD_linklib__