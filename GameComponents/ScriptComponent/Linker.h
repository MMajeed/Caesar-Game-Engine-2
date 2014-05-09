#ifndef __ScriptComponentGUARD_linklib__
#define __ScriptComponentGUARD_linklib__

	#define ScriptComponentLibFileName "ScriptComponent"  FileBuildType ".lib"

	#if defined(STATIC)
		#pragma comment (lib, ScriptComponentLibFileName)
		#define ScriptComponentDLL_API 
	#elif defined(DLL)	
		#ifdef ScriptComponentDLL_EXPORTS
			#define ScriptComponentDLL_API __declspec(dllexport) 
		#else
			#pragma comment (lib, ScriptComponentLibFileName)
			#define ScriptComponentDLL_API __declspec(dllimport) 
		#endif	
	#endif
	
#endif