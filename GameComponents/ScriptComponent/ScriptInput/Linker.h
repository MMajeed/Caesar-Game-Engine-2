#ifndef __ScriptInputGUARD_linklib__
#define __ScriptInputGUARD_linklib__

	#define ScriptInputLibFileName "ScriptInput"  FileBuildType ".lib"

	#if defined(STATIC)
		#pragma comment (lib, ScriptInputLibFileName)
		#define ScriptInputDLL_API 
	#elif defined(DLL)	
		#ifdef ScriptInputDLL_EXPORTS
			#define ScriptInputDLL_API __declspec(dllexport) 
		#else
			#pragma comment (lib, ScriptInputLibFileName)
			#define ScriptInputDLL_API __declspec(dllimport) 
		#endif	
	#endif
	
#endif