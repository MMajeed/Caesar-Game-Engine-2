#include "LuaKeysID.h"

#include <luabind\luabind.hpp>

#include <Keys.h>

void LuaKeysID::Register(lua_State *lua)
{
	luabind::object luaKeyTable = luabind::newtable(lua);
	
	luaKeyTable[Keys::ID]                   = Keys::ID;
	luaKeyTable[Keys::Class]                = Keys::Class;
	luaKeyTable[Keys::LOCATION]             = Keys::LOCATION;
	luaKeyTable[Keys::ROTATION]             = Keys::ROTATION;
	luaKeyTable[Keys::SCALE]                = Keys::SCALE;
	luaKeyTable[Keys::DIFFUSE]              = Keys::DIFFUSE;
	luaKeyTable[Keys::AMBIENT]              = Keys::AMBIENT;
	luaKeyTable[Keys::SPECULAR]             = Keys::SPECULAR;
	luaKeyTable[Keys::GRAPHICDRAWABLEID]    = Keys::GRAPHICDRAWABLEID;
	luaKeyTable[Keys::EYE]                  = Keys::EYE;
	luaKeyTable[Keys::TARGETMAGNITUDE]      = Keys::TARGETMAGNITUDE;
	luaKeyTable[Keys::UP]                   = Keys::UP;
	luaKeyTable[Keys::RADIANROLL]           = Keys::RADIANROLL;
	luaKeyTable[Keys::RADIANPITCH]          = Keys::RADIANPITCH;
	luaKeyTable[Keys::RADIANYAW]            = Keys::RADIANYAW;
	luaKeyTable[Keys::FOVANGLE]             = Keys::FOVANGLE;
	luaKeyTable[Keys::SCREENWIDTH]          = Keys::SCREENWIDTH;
	luaKeyTable[Keys::SCREENHEIGHT]         = Keys::SCREENHEIGHT;
	luaKeyTable[Keys::MINVIEWABLE]          = Keys::MINVIEWABLE;
	luaKeyTable[Keys::MAXVIEWABLE]	        = Keys::MAXVIEWABLE;
	luaKeyTable[Keys::MODELFILE]			= Keys::MODELFILE;
	luaKeyTable[Keys::VERTEXSHADERFILE]     = Keys::VERTEXSHADERFILE;
	luaKeyTable[Keys::PIXELSHADERFILE]	    = Keys::PIXELSHADERFILE;
	luaKeyTable[Keys::TEXTUREFILE]			= Keys::TEXTUREFILE;

	luabind::globals(lua)["Keys"] = luaKeyTable;
}