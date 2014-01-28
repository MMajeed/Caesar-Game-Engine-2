#ifndef __GUARD_linklib__
#define __GUARD_linklib__

#if defined(_DEBUG)
	#pragma comment (lib,"ForeignLibrary-mt-d.lib")
#elif !defined(_DEBUG)
	#pragma comment (lib,"ForeignLibrary-mt.lib")
#else
	#error link: no suitable library
#endif

#endif