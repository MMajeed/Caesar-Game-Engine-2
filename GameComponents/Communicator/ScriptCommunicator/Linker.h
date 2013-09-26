#ifndef __SCRIPTCOMMUNICATOR_GUARD_linklib__
#define __SCRIPTCOMMUNICATOR_GUARD_linklib__

#if defined(_DEBUG)
	#pragma comment (lib,"ScriptCommunicator-mt-d.lib")
#elif !defined(_DEBUG)
	#pragma comment (lib,"ScriptCommunicator-mt.lib")
#else
	#error link: no suitable library
#endif

#endif // __SCRIPTCOMMUNICATOR_GUARD_linklib__