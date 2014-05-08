#ifndef __InputCommunicatorGUARD_linklib__
#define __InputCommunicatorGUARD_linklib__

	#define InputCommunicatorLibFileName "InputCommunicator"  FileBuildType ".lib"

	#if defined(STATIC)
		#pragma comment (lib, InputCommunicatorLibFileName)
		#define InputCommunicatorDLL_API 
	#elif defined(DLL)	
		#ifdef InputCommunicatorDLL_EXPORTS
			#define InputCommunicatorDLL_API __declspec(dllexport) 
		#else	
			#pragma comment (lib, InputCommunicatorLibFileName)
			#define InputCommunicatorDLL_API __declspec(dllimport) 
		#endif	
	#endif
	
#endif