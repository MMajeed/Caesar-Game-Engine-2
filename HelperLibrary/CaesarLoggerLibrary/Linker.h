#ifndef __CaesarLoggerLibraryGUARD_linklib__
#define __CaesarLoggerLibraryGUARD_linklib__

#if defined(_DEBUG)
#pragma comment (lib,"CaesarLoggerLibrary-mt-d.lib")
#elif !defined(_DEBUG)
#pragma comment (lib,"CaesarLoggerLibrary-mt.lib")
#else
#error link: no suitable library
#endif

#endif