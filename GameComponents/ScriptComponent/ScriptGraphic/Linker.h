#ifndef __ScriptGraphicGUARD_linklib__
#define __ScriptGraphicGUARD_linklib__

	#define ScriptGraphicLibFileName "ScriptGraphic"  FileBuildType ".lib"

	#if defined(STATIC)
		#pragma comment (lib, ScriptGraphicLibFileName)
		#define ScriptGraphicDLL_API 
	#elif defined(DLL)	
		#ifdef ScriptGraphicDLL_EXPORTS
			#define ScriptGraphicDLL_API __declspec(dllexport) 
		#else
			#pragma comment (lib, ScriptGraphicLibFileName)
			#define ScriptGraphicDLL_API __declspec(dllimport) 
		#endif	
	#endif
	
#endif