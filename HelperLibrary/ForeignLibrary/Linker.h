#ifndef __GUARD_linklib__
#define __GUARD_linklib__

#if defined(_DEBUG)
#pragma comment (lib,"ForeignLibrary-mt-d.lib")
#elif defined(NDEBUGNO)
#pragma comment (lib,"ForeignLibrary-mt-no.lib")
#elif defined(NDEBUG)
#pragma comment (lib,"ForeignLibrary-mt.lib")
#else
	#error link: no suitable library
#endif

#endif