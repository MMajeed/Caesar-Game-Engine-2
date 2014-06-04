#ifndef __LuabindGUARD_linklib__
#define __LuabindGUARD_linklib__

	#define LuabindLibFileName "Luabind"  FileBuildType ".lib"

	#if defined(STATIC)
		#pragma comment (lib, LuabindLibFileName)
		#define LuabindDLL_API 
	#elif defined(DLL)	
		#ifdef LuabindDLL_EXPORTS
			#define LuabindDLL_API __declspec(dllexport) 
		#else	
			#pragma comment (lib, LuabindLibFileName)
			#define LuabindDLL_API //__declspec(dllimport) 
		#endif	
	#endif
	
	#if defined(DLL)
		#define LUABIND_DYNAMIC_LINK
	#endif
#endif