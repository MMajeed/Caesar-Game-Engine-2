#include "LuaModel.h"

#include "LuaManager.h"
#include <Model.h>
#include <string>

LuaModel::Model::Model()
{

}
LuaModel::Model::Model(std::shared_ptr<CHL::Model> model)
{
	this->model = model;
}
LuaModel::Model::operator std::shared_ptr<CHL::Model>()
{
	return this->model;
}
void LuaModel::Model::Register(lua_State *lua)
{
	luabind::module(lua)[
		luabind::class_<LuaModel::Model>("Model")
	];
}

LuaModel::Model LuaModel::GetFirstModel(std::string fileName)
{
	LuaModel::Model returnValue(std::make_shared<CHL::Model>(CHL::LoadModels(fileName)[0]));
	return returnValue;
}
luabind::object LuaModel::GetScene(std::string fileName)
{
	luabind::object returnValue = luabind::newtable(LuaManager::GetInstance().lua);
	
	std::vector<CHL::Model> models = CHL::LoadModels(fileName);
	for(std::size_t i = 0; i < models.size(); ++i)
	{
		returnValue[i] = LuaModel::Model(std::make_shared<CHL::Model>(models[i]));
	}
	return returnValue;
}

void LuaModel::RegisterAllLuaFunction(lua_State *lua)
{
	LuaModel::Model::Register(lua);
	luabind::module(lua)[
		luabind::def("LoadModel", LuaModel::GetFirstModel),
		luabind::def("LoadScene", LuaModel::GetScene)
	];
}