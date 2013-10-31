#ifndef __Object__
#define __Object__

#include "Linker.h"

#include <memory>

class Object
{
public:	
	virtual std::shared_ptr<Object> Clone() const = 0;
};

template<typename T>
class GenericObject : public Object
{
public:
	T item;
	GenericObject(T copy) : item(copy){}
	operator T() const{ return this->item; } 
	operator T&(){ return this->item; }
	T GetValue()const{ return this->item; } 
	T& GetValue(){ return this->item; }
	std::shared_ptr<Object> Clone()  const
	{
		return std::shared_ptr<Object>(new GenericObject(*this));
	}

	static std::shared_ptr<GenericObject<T>> CreateNew(T value){ return std::shared_ptr<GenericObject<T>>(new GenericObject<T>(value)); }
	static T& GetValue(std::shared_ptr<Object> value){ return std::dynamic_pointer_cast<GenericObject<T>>(value)->item; }
	static std::shared_ptr<GenericObject<T>> Cast(std::shared_ptr<Object> value){ return std::dynamic_pointer_cast<GenericObject<T>>(value); }
};

#endif //__Object__