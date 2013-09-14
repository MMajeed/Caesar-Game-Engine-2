#ifndef __BasicObject__
#define __BasicObject__

#include "Object.h"
#include <boost/numeric/ublas/matrix.hpp>

class BasicObject : public Object
{
public:
	BasicObject();

	boost::numeric::ublas::matrix<double> GetWorldLocation(boost::numeric::ublas::matrix<double> world, boost::numeric::ublas::matrix<double> prespective);
	boost::numeric::ublas::matrix<double> GetMatrix();

	const boost::numeric::ublas::vector<double> Location();
	void Location(boost::numeric::ublas::vector<double>);
	const boost::numeric::ublas::vector<double> Rotation();
	void Rotation(boost::numeric::ublas::vector<double>);
	const boost::numeric::ublas::vector<double> Scale();
	void Scale(boost::numeric::ublas::vector<double>);
	const boost::numeric::ublas::vector<double> Colour();
	void Colour(boost::numeric::ublas::vector<double>);

	struct BasicObjectKeys
	{
		const static std::string LOCATION;
		const static std::string ROTATION;
		const static std::string SCALE;
		const static std::string COLOUR;
	};

	static std::shared_ptr<BasicObject> ConvertObjectPtr(std::shared_ptr<Object> obj);
};

#endif //__BasicObject__