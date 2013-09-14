#ifndef __Model__
#define __Model__

// assimp include files. These three are usually needed.
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>

class Model
{
public:
	Model(std::string file);

	const struct aiScene* scene;
};

#endif //__Model__