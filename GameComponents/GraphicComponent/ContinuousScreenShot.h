#ifndef __ContinuousScreenShot__
#define __ContinuousScreenShot__

#include <string>
#include "TypedefObject.h"
#include <memory>

class ContinuousScreenShot
{
public:
	ContinuousScreenShot(const std::string& inputID) : ID(inputID){}

	virtual void Init()                                         = 0;
	virtual void Destory()                                      = 0;
	virtual void Update(double realTime, double deltaTime)      = 0;
	virtual void Snap(TypedefObject::ObjectVector& objects)     = 0;
	virtual std::shared_ptr<ContinuousScreenShot> clone() const = 0;
	virtual ~ContinuousScreenShot(){}

	const std::string ID;
	std::string TextureID;
};


#endif //__ContinuousScreenShot__
