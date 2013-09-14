#ifndef __ObjectManager__
#define __ObjectManager__

#include "Interface.h"
#include "Object.h"

#include <Singleton.h>
#include <VectorQueryable.h>
#include <memory>
#include <boost/thread/mutex.hpp>

class ObjectManager : public Interface, public CHL::Singelton<ObjectManager>
{
public:
	ObjectManager();
	virtual void Init();
	virtual void Update(double realTime, double deltaTime);
	virtual void Work();
	virtual void Shutdown();

	void Insert(std::shared_ptr<Object> obj);
	const CHL::VectorQueryable<std::shared_ptr<Object>> AllObjects();

	boost::mutex::scoped_lock lock;
protected:	
	CHL::VectorQueryable<std::shared_ptr<Object>> objects;
};

#endif //__ObjectManager__