#ifndef __Model__
#define __Model__

#include "Vector.h"
#include <string>
#include <vector>

struct aiScene;

class Model
{
public:
	Model(std::string file);

	const aiScene* scene;
	
	std::vector<CHL::Vec4> Pos() const;
	std::vector<CHL::Vec4> Normal() const;
	std::vector<CHL::Vec2> Texture() const;

	std::vector<unsigned int> Faces()  const;

};

#endif //__Model__