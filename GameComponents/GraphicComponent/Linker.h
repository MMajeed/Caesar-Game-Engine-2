#ifndef __GRAPHICCOMPONENT_GUARD_linklib__
#define __GRAPHICCOMPONENT_GUARD_linklib__

#if defined(_DEBUG)
#pragma comment (lib,"GraphicComponent-mt-d.lib")
#elif defined(NDEBUGNO)
#pragma comment (lib,"GraphicComponent-mt-no.lib")
#elif defined(NDEBUG)
#pragma comment (lib,"GraphicComponent-mt.lib")
#else
	#error link: no suitable library
#endif

#endif // __GRAPHICCOMPONENT_GUARD_linklib__