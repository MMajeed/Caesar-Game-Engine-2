#ifndef __ClearScreen__
#define __ClearScreen__

#include "Message.h"

#include <boost/numeric/ublas/vector.hpp>

class ClearScreenMessage : public Message
{
public:
	ClearScreenMessage(const boost::numeric::ublas::vector<double>& input);

	virtual Message::Status Work();

protected:
	boost::numeric::ublas::vector<double> colour;
};

#endif