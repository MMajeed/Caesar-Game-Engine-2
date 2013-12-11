#ifndef __Model__
#define __Model__

#include "Linker.h"
#include "Vector.h"
#include <string>
#include <vector>

namespace CHL
{
	class Model
	{
	public:
		Model();

		struct VerticesInfo
		{
			CHL::Vec3 Point;
			CHL::Vec3 Normal;
			CHL::Vec3 Texture;
		};
		std::vector<VerticesInfo> Vertices;
		std::vector<unsigned int> Faces;
		unsigned int NumberOfFaces;
		std::string name;

		void NormalizeTheModel();
		void TexturizeTheModel();
	};

	std::vector<Model> LoadModels(std::string fileName);
}

#endif //__Model__