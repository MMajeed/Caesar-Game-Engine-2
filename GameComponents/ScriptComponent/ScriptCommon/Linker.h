#ifndef __ScriptCommonGUARD_linklib__
#define __ScriptCommonGUARD_linklib__

	#define ScriptCommonLibFileName "ScriptCommon"  FileBuildType ".lib"

	#if defined(STATIC)
		#pragma comment (lib, ScriptCommonLibFileName)
		#define ScriptCommonDLL_API 
	#elif defined(DLL)	
		#ifdef ScriptCommonDLL_EXPORTS
			#define ScriptCommonDLL_API __declspec(dllexport) 
		#else
			#pragma comment (lib, ScriptCommonLibFileName)
			#define ScriptCommonDLL_API __declspec(dllimport) 
		#endif	
	#endif
	
#endif