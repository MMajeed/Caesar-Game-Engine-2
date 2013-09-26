#ifndef __INPUTCOMMUNICATOR_GUARD_linklib__
#define __INPUTCOMMUNICATOR_GUARD_linklib__

#if defined(_DEBUG)
	#pragma comment (lib,"InputCommunicator-mt-d.lib")
#elif !defined(_DEBUG)
	#pragma comment (lib,"InputCommunicator-mt.lib")
#else
	#error link: no suitable library
#endif

#endif // __INPUTCOMMUNICATOR_GUARD_linklib__