#ifndef __GraphicComponentGUARD_linklib__
#define __GraphicComponentGUARD_linklib__

	#define GraphicComponentLibFileName "GraphicComponent"  FileBuildType ".lib"

	#if defined(STATIC)
		#pragma comment (lib, GraphicComponentLibFileName)
		#define GraphicComponentDLL_API 
	#elif defined(DLL)	
		#ifdef GraphicComponentDLL_EXPORTS
			#define GraphicComponentDLL_API __declspec(dllexport) 
		#else	
			#define GraphicComponentDLL_API __declspec(dllimport) 
			#pragma comment (lib, GraphicComponentLibFileName)
		#endif	
	#endif
	
#endif