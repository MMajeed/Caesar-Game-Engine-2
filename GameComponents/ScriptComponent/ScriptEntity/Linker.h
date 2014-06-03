#ifndef __ScriptEntityGUARD_linklib__
#define __ScriptEntityGUARD_linklib__

	#define ScriptEntityLibFileName "ScriptEntity"  FileBuildType ".lib"

	#if defined(STATIC)
		#pragma comment (lib, ScriptEntityLibFileName)
		#define ScriptEntityDLL_API 
	#elif defined(DLL)	
		#ifdef ScriptEntityDLL_EXPORTS
			#define ScriptEntityDLL_API __declspec(dllexport) 
		#else
			#pragma comment (lib, ScriptEntityLibFileName)
			#define ScriptEntityDLL_API __declspec(dllimport) 
		#endif	
	#endif
	
#endif