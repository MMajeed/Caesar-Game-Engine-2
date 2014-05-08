#ifndef __EntityCommunicatorGUARD_linklib__
#define __EntityCommunicatorGUARD_linklib__

	#define EntityCommunicatorLibFileName "EntityCommunicator"  FileBuildType ".lib"

	#if defined(STATIC)
		#pragma comment (lib, EntityCommunicatorLibFileName)
		#define EntityCommunicatorDLL_API 
	#elif defined(DLL)	
		#ifdef EntityCommunicatorDLL_EXPORTS
			#define EntityCommunicatorDLL_API __declspec(dllexport) 
		#else	
			#pragma comment (lib, EntityCommunicatorLibFileName)
			#define EntityCommunicatorDLL_API __declspec(dllimport) 
		#endif	
	#endif
	
#endif