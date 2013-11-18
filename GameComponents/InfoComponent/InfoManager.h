#ifndef __ObjectManager__
#define __ObjectManager__

#include "Linker.h"
#include <Interface.h>
#include <Singleton.h>
#include <INFO.h>
#include <hash_map>

class InfoManager : public Interface, public CHL::Singelton<InfoManager>
{
protected:
	InfoManager();
public:
	virtual void Init();
	virtual void Update(double realTime, double deltaTime);
	virtual void Work();
	virtual void Shutdown();

	std::hash_map<std::string, SP_INFO> objects;

	friend CHL::Singelton<InfoManager>;
};

#endif //__ObjectManager__