#ifndef __ParallelWorker__
#define __ParallelWorker__

#include "iWorker.h"
#include <Interface.h>
#include <list>
#include <memory>
#include <thread>
#include <condition_variable>

class ParallelWorker : public iWorker
{
public:
	ParallelWorker(unsigned int fps);

	virtual void Run();

	virtual void ChangeFPS(unsigned int p);

	virtual void AddComponent(std::shared_ptr<Interface> pInterface,
							  unsigned int Priority = 0,
							  int Parameter = 0);
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