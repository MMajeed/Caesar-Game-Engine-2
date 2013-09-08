#ifndef __ClearScreen__
#define __ClearScreen__

#include "Interface.h"

#include <boost/numeric/ublas/vector.hpp>

class ClearScreenMessage : public Message
{
public:
	ClearScreenMessage(const boost::numeric::ublas::vector<double>& input);

	virtual void Proccess();

protected:
	boost::numeric::ublas::vector<double> colour;
};

#endif