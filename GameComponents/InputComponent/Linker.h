#ifndef __INPUTCOMPONENT_GUARD_linklib__
#define __INPUTCOMPONENT_GUARD_linklib__

#if defined(_DEBUG)
#pragma comment (lib,"InputComponent-mt-d.lib")
#elif defined(NDEBUGNO)
#pragma comment (lib,"InputComponent-mt-no.lib")
#elif defined(NDEBUG)
#pragma comment (lib,"InputComponent-mt.lib")
#else
	#error link: no suitable library
#endif

#endif // __INPUTCOMPONENT_GUARD_linklib__