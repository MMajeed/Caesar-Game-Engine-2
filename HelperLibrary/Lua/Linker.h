#ifndef __LuaGUARD_linklib__
#define __LuaGUARD_linklib__

	#define LuaLibFileName "Lua"  FileBuildType ".lib"

	#if defined(STATIC)
		#pragma comment (lib, LuaLibFileName)
		#define LuaDLL_API 
	#elif defined(DLL)	
		#ifdef LuaDLL_EXPORTS
			#define LuaDLL_API __declspec(dllexport) 
		#else	
			#pragma comment (lib, LuaLibFileName)
			#define LuaDLL_API //__declspec(dllimport) 
		#endif	
	#endif

	#if defined(DLL)
		#define LUA_BUILD_AS_DLL
	#endif
	
#endif