#ifndef __EntityComponentGUARD_linklib__
#define __EntityComponentGUARD_linklib__

	#define EntityComponentLibFileName "EntityComponent"  FileBuildType ".lib"

	#if defined(STATIC)
		#pragma comment (lib, EntityComponentLibFileName)
		#define EntityComponentDLL_API 
	#elif defined(DLL)	
		#ifdef EntityComponentDLL_EXPORTS
			#define EntityComponentDLL_API __declspec(dllexport) 
		#else	
			#pragma comment (lib, EntityComponentLibFileName)
			#define EntityComponentDLL_API __declspec(dllimport) 
		#endif	
	#endif
	
#endif