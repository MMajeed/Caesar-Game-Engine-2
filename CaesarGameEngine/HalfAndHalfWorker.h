#ifndef __HalfAndHalfWorker__
#define __HalfAndHalfWorker__

#include "iWorker.h"
#include <Interface.h>
#include <list>
#include <memory>
#include <thread>
#include <condition_variable>

class HalfAndHalfWorker : public iWorker
{
public:
	HalfAndHalfWorker(unsigned int fps);

	virtual void Run();

	virtual void ChangeFPS(unsigned int p);

	virtual void AddComponent(std::shared_ptr<Interface> pInterface,
							  unsigned int Priority = 0,
							  int Parameter = 0);

	enum ComponentParameter{First = 0, Parallel = 1, Last = 2};

protected:
	virtual void AddFirstComponent(std::shared_ptr<Interface> pInterface, unsigned int Priority);
	virtual void AddParallelComponent(std::shared_ptr<Interface> pInterface);
	virtual void AddLastComponent(std::shared_ptr<Interface> pInterface, unsigned int Priority);

	class CommonDLL_API ParallelManager
	{
	public:
		ParallelManager(std::shared_ptr<Interface> pInterface);

		virtual void Run();

		std::shared_ptr<Interface> Component;
		std::shared_ptr<std::thread> Thread;
		std::condition_variable cv;
		bool Running;
		std::mutex m;
	};

	struct ForwardManager
	{
		unsigned int Priority;
		std::shared_ptr<Interface> Component;
	};
	
	std::list<ForwardManager> FirstComponentList;
	std::list<std::shared_ptr<ParallelManager>> ParallelComponentList;
	std::list<ForwardManager> LastComponentList;

};

#endif