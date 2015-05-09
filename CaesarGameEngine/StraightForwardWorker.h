#ifndef __StraightForwardWorker__
#define __StraightForwardWorker__

#include "iWorker.h"
#include <Interface.h>
#include <list>
#include <memory>

class StraightForwardWorker : public iWorker
{
public:
	StraightForwardWorker(unsigned int fps);

	virtual void Run();

	virtual void ChangeFPS(unsigned int p);

	virtual void AddComponent(std::shared_ptr<Interface> pInterface,
							  unsigned int Priority = 0,
							  int Parameter = 0);
protected:
	struct ComponentInfo
	{
		unsigned int Priority;
		std::shared_ptr<Interface> Component;
	};

	std::list<ComponentInfo> ComponentList;
};

#endif