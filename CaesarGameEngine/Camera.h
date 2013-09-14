#ifndef __Camera__
#define __Camera__

#include "Object.h"
#include <boost/numeric/ublas/matrix.hpp>

class Camera : public Object
{
public:
	Camera(std::string ID);

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

	static const std::shared_ptr<Camera> GetFirstOrDefultCamera();
};

#endif //__Camera__