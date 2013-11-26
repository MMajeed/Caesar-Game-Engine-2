#ifndef __GRAPHICCOMMUNICATOR_GUARD_linklib__
#define __GRAPHICCOMMUNICATOR_GUARD_linklib__

#if defined(_DEBUG)
	#pragma comment (lib,"GraphicCommunicator-mt-d.lib")
#elif !defined(_DEBUG)
	#pragma comment (lib,"GraphicCommunicator-mt.lib")
#else
	#error link: no suitable library
#endif

#endif // __GRAPHICCOMMUNICATOR_GUARD_linklib__