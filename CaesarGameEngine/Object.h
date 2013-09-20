#ifndef __Object__
#define __Object__

#include <Queryable.h>
#include <string>
#include <boost/numeric/ublas/vector.hpp>

class Object
{
protected:
	CHL::MapQueryable<std::string, std::string> info;
public:
	Object();
	Object(CHL::MapQueryable<std::string, std::string> input);

	void Store(std::string key, const std::string& value);
	void Store(std::string key, const int value);
	void Store(std::string key, const double value);
	void Store(std::string key, const boost::numeric::ublas::vector<double>& value );

	bool Retrieve(std::string key, std::string& value) const;
	bool Retrieve(std::string key, int& value) const;
	bool Retrieve(std::string key, double& value) const;
	bool Retrieve(std::string key, boost::numeric::ublas::vector<double>& value) const;

	bool Exist(std::string key) const;

	operator CHL::MapQueryable<std::string, std::string>();

	virtual ~Object(){}
};

#endif //__Object__