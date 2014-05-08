#ifndef __AnimationComponentGUARD_linklib__
#define __AnimationComponentGUARD_linklib__

	#define AnimationComponentLibFileName "AnimationComponent"  FileBuildType ".lib"

	#if defined(STATIC)
		#pragma comment (lib, AnimationComponentLibFileName)
		#define AnimationComponentDLL_API 
	#elif defined(DLL)	
		#ifdef AnimationComponentDLL_EXPORTS
			#define AnimationComponentDLL_API __declspec(dllexport) 
		#else	
			#pragma comment (lib, AnimationComponentLibFileName)
			#define AnimationComponentDLL_API __declspec(dllimport) 
		#endif	
	#endif
	
#endif