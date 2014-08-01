#ifndef __AddBasicDrawableMessage__
#define __AddBasicDrawableMessage__

#include "Linker.h"

#include <Message.h>
#include <Model.h>
#include <string>
#include <memory>

namespace GraphicModelConfig
{
	GraphicCommunicatorDLL_API  std::string Create(std::shared_ptr<CHL::Model> model);
	GraphicCommunicatorDLL_API void Release(std::string ID);
};


#endif