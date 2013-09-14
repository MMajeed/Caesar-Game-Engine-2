#ifndef __Prespective__
#define __Prespective__

#include "Object.h"
#include <boost/numeric/ublas/matrix.hpp>

class Prespective : public Object
{
public:
	Prespective();

	boost::numeric::ublas::matrix<double> GetPrespectiveMatrix();

	const double FovAngle();
	void FovAngle(double);
	const double Width();
	void Width(double);
	const double Height();
	void Height(double);
	const double MinViewable();
	void MinViewable(double);
	const double MaxViewable();
	void MaxViewable(double);

	struct PrespectiveKeys
	{
		const static std::string FOVANGLE;
		const static std::string WIDTH;
		const static std::string HEIGHT;
		const static std::string MINVIEWABLE;
		const static std::string MAXCIEWABLE;
	};	

	static const std::shared_ptr<Prespective> GetFirstOrDefultPrespective();
};

#endif //__Prespective__