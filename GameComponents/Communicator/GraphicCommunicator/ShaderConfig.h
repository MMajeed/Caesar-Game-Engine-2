#ifndef __ShaderConfig__
#define __ShaderConfig

#include "Linker.h"
#include <string>

namespace ShaderConfig
{
	namespace Vertex
	{
		GraphicCommunicatorDLL_API std::string Create(std::string fileName);
		GraphicCommunicatorDLL_API void Release(std::string ID);
	}
	namespace Pixel
	{
		GraphicCommunicatorDLL_API std::string Create(std::string fileName);
		GraphicCommunicatorDLL_API void Release(std::string ID);
	}
	namespace Geometry
	{
		GraphicCommunicatorDLL_API std::string Create(std::string fileName);
		GraphicCommunicatorDLL_API void Release(std::string ID);
	}
}

#endif //__ShaderConfig