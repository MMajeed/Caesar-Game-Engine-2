#ifndef __Camera__
#define __Camera__

#include "Object.h"
#include <boost/numeric/ublas/matrix.hpp>

class Camera : public Object
{
public:
	Camera();

	void MoveForward(float delta);
	boost::numeric::ublas::matrix<double> GetViewMatrix();


	const boost::numeric::ublas::vector<double> Eye();
	const boost::numeric::ublas::vector<double> TargetMagnitude();
	const boost::numeric::ublas::vector<double> Up();
	void Eye(boost::numeric::ublas::vector<double>);
	void TargetMagnitude(boost::numeric::ublas::vector<double>);
	void Up(boost::numeric::ublas::vector<double>);
	const double RadianRoll();
	void RadianRoll(double);
	const double RadianPitch();
	void RadianPitch(double);
	const double RadianYaw();
	void RadianYaw(double);

	struct CameraKeys
	{
		const static std::string EYE;
		const static std::string TARGETMAGNITUDE;
		const static std::string UP;
		const static std::string RADIANROLL;
		const static std::string RADIANPITCH;
		const static std::string RADIANYAW;
	};
};

#endif //__Camera__