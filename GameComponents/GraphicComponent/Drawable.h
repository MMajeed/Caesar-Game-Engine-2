#ifndef __iObjectDrawable__
#define __iObjectDrawable__

#include "Linker.h"

#include <string>
#include <limits>
#include <Converter.h>
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.
#include <Queryable.h>

class Drawable
{
public:
#undef max
	Drawable(){this->ID = CHL::ToString(boost::uuids::random_generator()()); }
	virtual void Init()															= 0;
	virtual void Destory()														= 0;
	virtual void Update(float delta)											= 0;
	virtual void Draw(const CHL::MapQ<std::string, std::string>& object)	= 0;
	virtual std::shared_ptr<Drawable>clone() const								= 0;
	virtual float GetOrder(){return std::numeric_limits<float>::max();}

	virtual ~Drawable(){}

	std::string	ID;
};


#endif //__iObjectDrawable__