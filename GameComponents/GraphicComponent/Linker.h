#ifndef __GRAPHICCOMPONENT_GUARD_linklib__
#define __GRAPHICCOMPONENT_GUARD_linklib__

#if defined(_DEBUG)
	#pragma comment (lib,"GraphicComponent-mt-d.lib")
#elif !defined(_DEBUG)
	#pragma comment (lib,"GraphicComponent-mt.lib")
#else
	#error link: no suitable library
#endif

#endif // __GRAPHICCOMPONENT_GUARD_linklib__