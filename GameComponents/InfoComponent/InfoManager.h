#ifndef __ObjectManager__
#define __ObjectManager__

#include "Linker.h"
#include <Interface.h>
#include "Info.h"

#include <Singleton.h>
#include <Queryable.h>
#include <memory>

class InfoManager : public Interface, public CHL::Singelton<InfoManager>
{
protected:
	InfoManager();
public:
	virtual void Init();
	virtual void Update(double realTime, double deltaTime);
	virtual void Work();
	virtual void Shutdown();

	void Insert(const Info& obj);
	void UpdateObject(std::string ID, std::string infoID, std::shared_ptr<Object> info);
	const CHL::MapQ<std::string, Info>& AllObjects();
	Info GetObjectInfo(std::string ID);
protected:	
	CHL::MapQ<std::string, Info> objects;

	friend CHL::Singelton<InfoManager>;
};

#endif //__ObjectManager__