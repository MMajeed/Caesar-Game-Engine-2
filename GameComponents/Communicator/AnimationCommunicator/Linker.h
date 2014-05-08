#ifndef __AnimationCommunicatorGUARD_linklib__
#define __AnimationCommunicatorGUARD_linklib__

	#define AnimationCommunicatorLibFileName "AnimationCommunicator"  FileBuildType ".lib"

	#if defined(STATIC)
		#pragma comment (lib, AnimationCommunicatorLibFileName)
		#define AnimationCommunicatorDLL_API 
	#elif defined(DLL)	
		#ifdef AnimationCommunicatorDLL_EXPORTS
			#define AnimationCommunicatorDLL_API __declspec(dllexport) 
		#else	
			#pragma comment (lib, AnimationCommunicatorLibFileName)
			#define AnimationCommunicatorDLL_API __declspec(dllimport) 
		#endif	
	#endif
	
#endif