#ifndef __StraightForwardWorker__
#define __StraightForwardWorker__

#include "Interface.h"
#include <list>
#include <memory>

class StraightForwardWorker
{
public:
	StraightForwardWorker();

	virtual void Run();

	virtual void AddComponent(std::shared_ptr<Interface> pInterface, unsigned int Priority);
protected:
	struct ComponentInfo
	{
		unsigned int Priority;
		std::shared_ptr<Interface> Component;
	};

	std::list<ComponentInfo> ComponentList;
	unsigned int NumberOfFramePerSeconds;
};

#endif