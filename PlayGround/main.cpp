extern "C" {
#include <lua5.1.5\lua.h>
#include <lua5.1.5\lualib.h>
#include <lua5.1.5\lauxlib.h>
}

int main()
{
	lua_State *lua = lua_open();

	
	lua_pushcfunction(lua,luaopen_base);
	lua_call(lua,0,0);
	lua_pushcfunction(lua,luaopen_table);
	lua_call(lua,0,0);
	lua_pushcfunction(lua,luaopen_io);
	lua_call(lua,0,0);
	lua_pushcfunction(lua,luaopen_os);
	lua_call(lua,0,0);
	lua_pushcfunction(lua,luaopen_string);
	lua_call(lua,0,0);
	lua_pushcfunction(lua,luaopen_math);
	lua_call(lua,0,0);
	lua_pushcfunction(lua,luaopen_debug);
	lua_call(lua,0,0);
	lua_pushcfunction(lua,luaopen_package);
	lua_call(lua,0,0);

}