#ifndef __CaesarMathLibraryGUARD_linklib__
#define __CaesarMathLibraryGUARD_linklib__

#if defined(_DEBUG)
#pragma comment (lib,"CaesarMathLibrary-mt-d.lib")
#elif defined(NDEBUGNO)
#pragma comment (lib,"CaesarMathLibrary-mt-no.lib")
#elif defined(NDEBUG)
#pragma comment (lib,"CaesarMathLibrary-mt.lib")
#else
#error link: no suitable library
#endif

#endif