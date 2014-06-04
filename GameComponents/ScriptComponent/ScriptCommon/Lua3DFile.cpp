#include "Lua3DFile.h"

#include "LuaManager.h"
#include "LuaModel.h"
#include "LuaAnimation.h"
#include "LuaNode.h"
#include <3DLoader.h>
#include <string>
#include <Logger.h>

namespace Lua3DFile
{
	luabind::object  LoadScene(std::string fileName)
	{
		lua_State *lua = LuaManager::GetInstance().lua;
		luabind::object outModels = luabind::newtable(lua);
		luabind::object outAnimation = luabind::newtable(lua);

		std::vector<std::shared_ptr<CHL::Model>> models;
		std::vector<std::shared_ptr<CHL::Animation>> animation;
		std::shared_ptr<CHL::Node> rootNode;
		CHL::Load3DFile(fileName, models, animation, rootNode);
		for(std::size_t i = 0; i < models.size(); ++i)
		{
			outModels[i + 1] = LuaModel::Model(models[i]);
		}
		for(std::size_t i = 0; i < animation.size(); ++i)
		{
			outAnimation[i + 1] = LuaAnimation::Animation(animation[i]);
		}
		LuaNode::Node outRootNode = rootNode;

		luabind::object luaSceneTable = luabind::newtable(lua);
		luaSceneTable["Model"] = outModels;
		luaSceneTable["Animation"] = outAnimation;
		luaSceneTable["RootNode"] = outRootNode;
		return luaSceneTable;
	}

	void RegisterAllLuaFunction(lua_State *lua)
	{
		luabind::module(lua)[
			luabind::def("LoadScene", Lua3DFile::LoadScene)
		];
	}
}