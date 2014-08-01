#include "LuaGraphicModel.h"

#include <exception>
#include <Converter.h>
#include "ScriptManager.h"
#include <GraphicCommunicator\GraphicModelConfig.h>
#include <Keys.h>
#include <stdexcept>
#include <Logger.h>
#include <GenericLuaObject.h>

namespace LuaGraphicModel
{
	GraphicModel::GraphicModel(const LuaModel::Model& model)
	{
		this->ID = GraphicModelConfig::Create(model.model);
	}
	GraphicModel::GraphicModel(const GenericLuaObject& v) : GenericLuaObject(v){}
	void GraphicModel::Release()
	{
		GraphicModelConfig::Release(this->ID);
	}
	void GraphicModel::Register(lua_State *lua)
	{
		luabind::module(lua)[
			luabind::class_<GraphicModel, GenericLuaObject>("GraphicModel")
				.def(luabind::constructor<const LuaModel::Model&>())
				.def(luabind::constructor<const GenericLuaObject&>())
				.def("Release", &GraphicModel::Release)
		];
	}
	//***********************************************************************//
	void RegisterAllLuaFunction(lua_State *lua)
	{
		GraphicModel::Register(lua);
	}
}