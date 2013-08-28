#ifndef __GraphicManager__
#define __GraphicManager__

#include <Singleton.h>
#include <MapQueryable.h>

#include "Interface.h"

class GraphicManager : public Interface, public CHL::Singelton<GraphicManager>
{
public:
	virtual void Init();
	virtual void Update(double realTime, double deltaTime);
	virtual void Run();
	virtual void Shutdown();
};

#endif //__GraphicManager__