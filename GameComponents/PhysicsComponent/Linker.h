#ifndef __PhysicsComponent_GUARD_linklib__
#define __PhysicsComponent_GUARD_linklib__

#if defined(_DEBUG)
#pragma comment (lib,"PhysicsComponent-mt-d.lib")
#elif defined(NDEBUGNO)
#pragma comment (lib,"PhysicsComponent-mt-no.lib")
#elif defined(NDEBUG)
#pragma comment (lib,"PhysicsComponent-mt.lib")
#else
#error link: no suitable library
#endif

#endif // __PhysicsComponent_GUARD_linklib__