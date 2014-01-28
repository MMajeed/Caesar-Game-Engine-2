#ifndef __CaesarHelperLibraryGUARD_linklib__
#define __CaesarHelperLibraryGUARD_linklib__

#if defined(_DEBUG)
	#pragma comment (lib,"CaesarHelperLibrary-mt-d.lib")
#elif !defined(_DEBUG)
	#pragma comment (lib,"CaesarHelperLibrary-mt.lib")
#else
	#error link: no suitable library
#endif

#endif