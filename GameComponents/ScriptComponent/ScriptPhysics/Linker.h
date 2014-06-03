#ifndef __ScriptPhysicsGUARD_linklib__
#define __ScriptPhysicsGUARD_linklib__

	#define ScriptPhysicsLibFileName "ScriptPhysics"  FileBuildType ".lib"

	#if defined(STATIC)
		#pragma comment (lib, ScriptPhysicsLibFileName)
		#define ScriptPhysicsDLL_API 
	#elif defined(DLL)	
		#ifdef ScriptPhysicsDLL_EXPORTS
			#define ScriptPhysicsDLL_API __declspec(dllexport) 
		#else
			#pragma comment (lib, ScriptPhysicsLibFileName)
			#define ScriptPhysicsDLL_API __declspec(dllimport) 
		#endif	
	#endif
	
#endif