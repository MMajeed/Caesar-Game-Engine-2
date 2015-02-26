#ifndef __ParallelWorker__
#define __ParallelWorker__

#include "Interface.h"
#include <list>
#include <memory>
#include <thread>
#include <condition_variable>

class ParallelWorker
{
public:
	virtual void Run();

	virtual void AddComponent(std::shared_ptr<Interface> pInterface, unsigned int NumberOfFramePerSeconds);
protected:
	class CommonDLL_API ComponentManager
	{
	public:
		ComponentManager(std::shared_ptr<Interface> pInterface, unsigned int NumberOfFramePerSeconds);

		virtual void Run();

		std::shared_ptr<Interface> Component;
		unsigned int NumberOfFramePerSeconds;
		std::shared_ptr<std::thread> Thread;
		std::condition_variable cv;
		bool Running;
		std::mutex m;
	};

	std::list<std::shared_ptr<ComponentManager>> ComponentList;
};

#endif