#ifndef __Error__
#define __Error__

#include <exception>
#include <stdexcept>
#include <Singleton.h>

class Error : public CHL::Singelton<Error>
{
private:
	std::exception_ptr eptr;
public:
	void Check();
	void SetError(std::exception_ptr inputEptr);
};

#endif