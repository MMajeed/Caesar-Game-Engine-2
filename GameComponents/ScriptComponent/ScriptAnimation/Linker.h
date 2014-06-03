#ifndef __ScriptAnimationGUARD_linklib__
#define __ScriptAnimationGUARD_linklib__

	#define ScriptAnimationLibFileName "ScriptAnimation"  FileBuildType ".lib"

	#if defined(STATIC)
		#pragma comment (lib, ScriptAnimationLibFileName)
		#define ScriptAnimationDLL_API 
	#elif defined(DLL)	
		#ifdef ScriptAnimationDLL_EXPORTS
			#define ScriptAnimationDLL_API __declspec(dllexport) 
		#else
			#pragma comment (lib, ScriptAnimationLibFileName)
			#define ScriptAnimationDLL_API __declspec(dllimport) 
		#endif	
	#endif
	
#endif