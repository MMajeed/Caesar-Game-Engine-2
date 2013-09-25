#ifndef __Model__
#define __Model__

#include <boost/numeric/ublas/matrix.hpp>

#include <string>
#include <vector>

struct aiScene;

class Model
{
public:
	Model(std::string file);

	const aiScene* scene;
	
	std::vector<boost::numeric::ublas::vector<double>> Pos() const;
	std::vector<boost::numeric::ublas::vector<double>> Normal() const;
	std::vector<boost::numeric::ublas::vector<double>> Texture() const;

	std::vector<unsigned int> Faces()  const;

};

#endif //__Model__