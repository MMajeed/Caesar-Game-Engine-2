#ifndef __Object__
#define __Object__

#include <hash_map>
#include <string>
#include <boost/numeric/ublas/vector.hpp>

class Object
{
protected:
	std::hash_map<std::string, std::string> info;
public:
	Object();

	void Store(std::string key, const std::string& value);
	void Store(std::string key, const int value);
	void Store(std::string key, const double value);
	void Store(std::string key, const boost::numeric::ublas::vector<double>& value );

	bool Retrieve(std::string key, std::string& value);
	bool Retrieve(std::string key, int& value);
	bool Retrieve(std::string key, double& value);
	bool Retrieve(std::string key, boost::numeric::ublas::vector<double>& value);

	struct Keys
	{
		const static std::string ID;
	};
};

#endif //__Object__