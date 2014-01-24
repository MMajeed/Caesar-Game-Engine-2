#ifndef __ANIMATIONCOMPONENT_GUARD_linklib__
#define __ANIMATIONCOMPONENT_GUARD_linklib__

#if defined(_DEBUG)
#pragma comment (lib,"AnimationComponent-mt-d.lib")
#elif !defined(_DEBUG)
#pragma comment (lib,"AnimationComponent-mt.lib")
#else
#error link: no suitable library
#endif

#endif // __ANIMATIONCOMPONENT_GUARD_linklib__