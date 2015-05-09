#ifndef __iWorker__
#define __iWorker__

#include <Interface.h>
#include <memory>

class iWorker 
{
public:
	iWorker(unsigned int fps);

	virtual void Run() = 0;

	virtual void ChangeFPS(unsigned int p) = 0;

	virtual void AddComponent(std::shared_ptr<Interface> pInterface,
							  unsigned int Priority = 0,
							  int Parameter = 0) = 0;
protected:
	std::atomic<bool> Running;
	std::atomic<unsigned int> NumFPS;
};

#endif