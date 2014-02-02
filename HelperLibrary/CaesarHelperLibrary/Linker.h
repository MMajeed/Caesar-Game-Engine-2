#ifndef __CaesarHelperLibraryGUARD_linklib__
#define __CaesarHelperLibraryGUARD_linklib__

#if defined(_DEBUG)
#pragma comment (lib,"CaesarHelperLibrary-mt-d.lib")
#elif defined(NDEBUGNO)
#pragma comment (lib,"CaesarHelperLibrary-mt-no.lib")
#elif defined(NDEBUG)
#pragma comment (lib,"CaesarHelperLibrary-mt.lib")
#else
	#error link: no suitable library
#endif

#endif