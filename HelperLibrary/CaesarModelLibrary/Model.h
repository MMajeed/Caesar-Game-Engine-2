#ifndef __Model__
#define __Model__

#include "Linker.h"
#include <Vector.h>
#include <string>
#include <vector>

namespace CHL
{
	class CaesarModelLibraryDLL_API Model
	{
	public:
		Model();

		std::vector<CML::Vec3> Vertices;
		std::vector<CML::Vec3> Normal;
		std::vector<CML::Vec3> Tangents;
		std::vector<CML::Vec3> Bitangents;
		std::vector<CML::Vec4> Color;
		std::vector<CML::Vec3> Texture;

		std::vector<unsigned int> Faces;
		unsigned int NumberOfFaces;

		std::string name;
	};
}

#endif //__Model__