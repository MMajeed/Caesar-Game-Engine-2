#ifndef __iObjectDrawable__
#define __iObjectDrawable__

#include "Linker.h"
#include <ObjectINFO.h>
#include <string>
#include "SceneInfo.h"

class Drawable
{
protected:
	Drawable(){}
public:
	virtual void Init()										    = 0;
	virtual void Destory()									    = 0;
	virtual void Update(double realTime, double deltaTime)      = 0;
	virtual void Draw(std::shared_ptr<ObjectINFO> object,
					  const SceneInfo& si)                      = 0;
	virtual void DrawShadow(std::shared_ptr<ObjectINFO> object,
							const SceneInfo& si)                = 0;
	virtual std::shared_ptr<Drawable>clone() const			    = 0;
	virtual ~Drawable(){}
};


#endif //__iObjectDrawable__