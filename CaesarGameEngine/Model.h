#ifndef __Model__
#define __Model__

#include <boost/numeric/ublas/matrix.hpp>

// assimp include files. These three are usually needed.
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <vector>
class Model
{
public:
	Model(std::string file);

	const struct aiScene* scene;
	
	std::vector<boost::numeric::ublas::vector<double>> Pos() const;
	std::vector<boost::numeric::ublas::vector<double>> Normal() const;
	std::vector<boost::numeric::ublas::vector<double>> Texture() const;

	std::vector<unsigned int> Faces()  const;

};

#endif //__Model__