#ifndef __PhysicsCommunicator_GUARD_linklib__
#define __PhysicsCommunicator_GUARD_linklib__

#if defined(_DEBUG)
#pragma comment (lib,"PhysicsCommunicator-mt-d.lib")
#elif defined(NDEBUGNO)
#pragma comment (lib,"PhysicsCommunicator-mt-no.lib")
#elif defined(NDEBUG)
#pragma comment (lib,"PhysicsCommunicator-mt.lib")
#else
#error link: no suitable library
#endif

#endif // __PhysicsCommunicator_GUARD_linklib__