#ifndef __GraphicCommunicatorGUARD_linklib__
#define __GraphicCommunicatorGUARD_linklib__

	#define GraphicCommunicatorLibFileName "GraphicCommunicator"  FileBuildType ".lib"

	#if defined(STATIC)
		#pragma comment (lib, GraphicCommunicatorLibFileName)
		#define GraphicCommunicatorDLL_API 
	#elif defined(DLL)	
		#ifdef GraphicCommunicatorDLL_EXPORTS
			#define GraphicCommunicatorDLL_API __declspec(dllexport) 
		#else	
			#pragma comment (lib, GraphicCommunicatorLibFileName)
			#define GraphicCommunicatorDLL_API //__declspec(dllimport) 
		#endif	
	#endif
	
#endif