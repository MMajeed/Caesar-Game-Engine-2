#ifndef __INPUTCOMMUNICATOR_GUARD_linklib__
#define __INPUTCOMMUNICATOR_GUARD_linklib__

#if defined(_DEBUG)
#pragma comment (lib,"InputCommunicator-mt-d.lib")
#elif defined(NDEBUGNO)
#pragma comment (lib,"InputCommunicator-mt-no.lib")
#elif defined(NDEBUG)
#pragma comment (lib,"InputCommunicator-mt.lib")
#else
	#error link: no suitable library
#endif

#endif // __INPUTCOMMUNICATOR_GUARD_linklib__