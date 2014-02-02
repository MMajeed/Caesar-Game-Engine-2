#ifndef __GRAPHICCOMMUNICATOR_GUARD_linklib__
#define __GRAPHICCOMMUNICATOR_GUARD_linklib__

#if defined(_DEBUG)
#pragma comment (lib,"GraphicCommunicator-mt-d.lib")
#elif defined(NDEBUGNO)
#pragma comment (lib,"GraphicCommunicator-mt-no.lib")
#elif defined(NDEBUG)
#pragma comment (lib,"GraphicCommunicator-mt.lib")
#else
	#error link: no suitable library
#endif

#endif // __GRAPHICCOMMUNICATOR_GUARD_linklib__