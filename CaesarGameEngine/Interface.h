#ifndef __Interface__
#define __Interface__

#include <map>

class Interface
{
public:
	virtual void Init() = 0;
	virtual void Update(double realTime, double deltaTime) = 0;
	virtual void Run() = 0;
	virtual void Shutdown() = 0;
};

#endif