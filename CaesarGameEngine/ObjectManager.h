#ifndef __ObjectManager__
#define __ObjectManager__

#include "Interface.h"
#include "Object.h"

#include <Singleton.h>
#include <Queryable.h>
#include <memory>

class ObjectManager : public Interface, public CHL::Singelton<ObjectManager>
{
protected:
	ObjectManager();
public:
	virtual void Init();
	virtual void Update(double realTime, double deltaTime);
	virtual void Work();
	virtual void Shutdown();

	void Insert(std::shared_ptr<Object> obj);
	const CHL::VectorQueryable<std::shared_ptr<Object>> AllObjects();
protected:	
	CHL::VectorQueryable<std::shared_ptr<Object>> objects;

	friend CHL::Singelton<ObjectManager>;
};

#endif //__ObjectManager__