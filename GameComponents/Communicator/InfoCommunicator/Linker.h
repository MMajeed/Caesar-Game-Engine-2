#ifndef __INFOCOMMUNICATOR_GUARD_linklib__
#define __INFOCOMMUNICATOR_GUARD_linklib__

#if defined(_DEBUG)
	#pragma comment (lib,"InfoCommunicator-mt-d.lib")
#elif !defined(_DEBUG)
	#pragma comment (lib,"InfoCommunicator-mt.lib")
#else
	#error link: no suitable library
#endif

#endif // __INFOCOMMUNICATOR_GUARD_linklib__