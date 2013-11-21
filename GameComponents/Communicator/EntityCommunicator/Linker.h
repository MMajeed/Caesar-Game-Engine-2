#ifndef __EntityCommunicator_GUARD_linklib__
#define __EntityCommunicator_GUARD_linklib__

#if defined(_DEBUG)
	#pragma comment (lib,"EntityCommunicator-mt-d.lib")
#elif !defined(_DEBUG)
	#pragma comment (lib,"EntityCommunicator-mt.lib")
#else
	#error link: no suitable library
#endif

#endif // __EntityCommunicator_GUARD_linklib__
