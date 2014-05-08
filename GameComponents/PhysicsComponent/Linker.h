#ifndef __PhysicsComponentGUARD_linklib__
#define __PhysicsComponentGUARD_linklib__

	#define PhysicsComponentLibFileName "PhysicsComponent"  FileBuildType ".lib"

	#if defined(STATIC)
		#pragma comment (lib, PhysicsComponentLibFileName)
		#define PhysicsComponentDLL_API 
	#elif defined(DLL)	
		#ifdef PhysicsComponentDLL_EXPORTS
			#define PhysicsComponentDLL_API __declspec(dllexport) 
		#else	
			#pragma comment (lib, PhysicsComponentLibFileName)
			#define PhysicsComponentDLL_API __declspec(dllimport) 
		#endif	
	#endif
	
#endif