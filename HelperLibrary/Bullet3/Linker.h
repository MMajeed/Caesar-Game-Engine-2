#ifndef __Bullet3GUARD_linklib__
#define __Bullet3GUARD_linklib__

	#define Bullet3LibFileName "Bullet3"  FileBuildType ".lib"

	#if defined(STATIC)
		#pragma comment (lib, Bullet3LibFileName)
		#define Bullet3DLL_API 
	#elif defined(DLL)	
		#ifdef Bullet3DLL_EXPORTS
			#define Bullet3DLL_API __declspec(dllexport) 
		#else	
			#pragma comment (lib, Bullet3LibFileName)
			#define Bullet3DLL_API //__declspec(dllimport) 
		#endif	
	#endif
	
#endif