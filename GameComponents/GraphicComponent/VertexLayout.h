#ifndef __VertexLayout__
#define __VertexLayout__

#include "Linker.h"

#include <string>
#include <DXGIFormat.h>

struct GraphicComponentDLL_API VertexLayout
{
	std::string Name;
	DXGI_FORMAT Format;
	unsigned int Size;
	unsigned int Offset;
};

namespace InputLayoutName
{
	const static std::string Position = "Position";
	const static std::string Normal = "Normal";
	const static std::string Tangents = "Tangents";
	const static std::string Bitangents = "Bitangents";
	const static std::string Color = "Color";
	const static std::string Texture = "Texture";
}

namespace InputLayoutType
{
	const static DXGI_FORMAT Position = DXGI_FORMAT_R32G32B32A32_FLOAT;
	const static DXGI_FORMAT Normal = DXGI_FORMAT_R32G32B32A32_FLOAT;
	const static DXGI_FORMAT Tangents = DXGI_FORMAT_R32G32B32A32_FLOAT;
	const static DXGI_FORMAT Bitangents = DXGI_FORMAT_R32G32B32A32_FLOAT;
	const static DXGI_FORMAT Color = DXGI_FORMAT_R32G32B32A32_FLOAT;
	const static DXGI_FORMAT Texture = DXGI_FORMAT_R32G32B32A32_FLOAT;
}

#endif //__VertexLayout__