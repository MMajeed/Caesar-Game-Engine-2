#ifndef __ObjectManager__
#define __ObjectManager__

#include "Linker.h"
#include <Interface.h>
#include "Info.h"

#include <Singleton.h>
#include <vector>
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
	void DeleteInfo(std::string ID, std::string infoID);
	const std::hash_map<std::string, Info>& AllObjects();
	const Info& GetObjectInfo(std::string ID);
protected:	
	std::hash_map<std::string, Info> objects;

	friend CHL::Singelton<InfoManager>;
};

#endif //__ObjectManager__