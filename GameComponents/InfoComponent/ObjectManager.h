#ifndef __ObjectManager__
#define __ObjectManager__

#include "Linker.h"
#include <Interface.h>
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

	void Insert(Object obj);
	void UpdateObject(std::string ID, std::string infoID, std::string info);
	const CHL::VectorQ<Object> AllObjects();
	Object GetObjectInfo(std::string ID);
protected:	
	CHL::VectorQ<Object> objects;

	friend CHL::Singelton<ObjectManager>;
};

#endif //__ObjectManager__