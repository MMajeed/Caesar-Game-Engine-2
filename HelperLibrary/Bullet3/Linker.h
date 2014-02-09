#ifndef __Bullet3GUARD_linklib__
#define __Bullet3GUARD_linklib__

#if defined(_DEBUG)
#pragma comment (lib,"Bullet3-mt-d.lib")
#elif defined(NDEBUGNO)
#pragma comment (lib,"Bullet3-mt-no.lib")
#elif defined(NDEBUG)
#pragma comment (lib,"Bullet3-mt.lib")
#else
#error link: no suitable library
#endif

#endif