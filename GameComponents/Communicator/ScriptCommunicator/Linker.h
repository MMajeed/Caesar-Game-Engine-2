#ifndef __ScriptCommunicatorGUARD_linklib__
#define __ScriptCommunicatorGUARD_linklib__

	#define ScriptCommunicatorLibFileName "ScriptCommunicator"  FileBuildType ".lib"

	#if defined(STATIC)
		#pragma comment (lib, ScriptCommunicatorLibFileName)
		#define ScriptCommunicatorDLL_API 
	#elif defined(DLL)	
		#ifdef ScriptCommunicatorDLL_EXPORTS
			#define ScriptCommunicatorDLL_API __declspec(dllexport) 
		#else	
			#pragma comment (lib, ScriptCommunicatorLibFileName)
			#define ScriptCommunicatorDLL_API __declspec(dllimport) 
		#endif	
	#endif
	
#endif