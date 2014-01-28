#include "Model.h"
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include "Logger.h"

namespace CHL
{
	Model::Model()
	{
		this->NumberOfFaces = 3;
	}
}