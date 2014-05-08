#ifndef __PhysicsCommunicatorGUARD_linklib__
#define __PhysicsCommunicatorGUARD_linklib__

	#define PhysicsCommunicatorLibFileName "PhysicsCommunicator"  FileBuildType ".lib"

	#if defined(STATIC)
		#pragma comment (lib, PhysicsCommunicatorLibFileName)
		#define PhysicsCommunicatorDLL_API 
	#elif defined(DLL)	
		#ifdef PhysicsCommunicatorDLL_EXPORTS
			#define PhysicsCommunicatorDLL_API __declspec(dllexport) 
		#else	
			#pragma comment (lib, PhysicsCommunicatorLibFileName)
			#define PhysicsCommunicatorDLL_API __declspec(dllimport) 
		#endif	
	#endif
	
#endif