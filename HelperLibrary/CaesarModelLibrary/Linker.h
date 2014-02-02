#ifndef __CAESARMODELLIBRARYGUARD_linklib__
#define __CAESARMODELLIBRARYGUARD_linklib__

#if defined(_DEBUG)
#pragma comment (lib,"CaesarModelLibrary-mt-d.lib")
#elif defined(NDEBUGNO)
#pragma comment (lib,"CaesarModelLibrary-mt-no.lib")
#elif defined(NDEBUG)
#pragma comment (lib,"CaesarModelLibrary-mt.lib")
#else
#error link: no suitable library
#endif

#endif