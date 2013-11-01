#ifndef __iObjectDrawable__
#define __iObjectDrawable__

#include "Linker.h"

#include <string>
#include "TypedefObject.h"

class Drawable
{
public:
	Drawable(const std::string& inputID) : ID(inputID){}
	virtual void Init()										= 0;
	virtual void Destory()									= 0;
	virtual void Update(double realTime, double deltaTime)  = 0;
	virtual void Draw(TypedefObject::ObjectInfo& object)	= 0;
	virtual std::shared_ptr<Drawable>clone() const			= 0;
	virtual ~Drawable(){}

	const std::string ID;
};


#endif //__iObjectDrawable__