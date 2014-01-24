#ifndef __AddBasicDrawableMessage__
#define __AddBasicDrawableMessage__

#include "Linker.h"

#include <Message.h>
#include <Model.h>
#include <string>
#include <memory>

namespace BasicDrawableConfig
{
	enum class CULL_MODE { CULL_NONE = 1, CULL_FRONT = 2, CULL_BACK = 3 };
	enum class FILL_MODE { FILL_WIREFRAME = 2, FILL_SOLID = 3 };

	std::string Create(std::shared_ptr<CHL::Model> model,
					   std::string	vertexFileName,
					   std::string	pixelFileName,
					   std::string	GeometryFileName,
					   BasicDrawableConfig::CULL_MODE cullMode,
					   BasicDrawableConfig::FILL_MODE fillMode);
	std::string Create2D(std::shared_ptr<CHL::Model> model,
						 std::string	vertexFileName,
						 std::string	pixelFileName,
						 std::string	GeometryFileName,
						 BasicDrawableConfig::CULL_MODE cullMode,
						 BasicDrawableConfig::FILL_MODE fillMode);
	
	void ChangeModel(std::string ID, std::shared_ptr<CHL::Model> model);
	void ChangeRastersizerState(std::string ID,
								BasicDrawableConfig::CULL_MODE cullMode,
								BasicDrawableConfig::FILL_MODE fillMode);
	void ChangeVS(std::string ID, std::string fileName);
	void ChangeGS(std::string ID, std::string fileName);
	void ChangePS(std::string ID, std::string fileName);

	void Release(std::string ID);
};


#endif