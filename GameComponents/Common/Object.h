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
	std::shared_ptr<Object> Clone()  const{ return std::make_shared<GenericObject<T>>(*this); }

	static std::shared_ptr<GenericObject<T>> CreateNew(const T& value){ return std::make_shared<GenericObject<T>>(value); }
	static T& GetValue(std::shared_ptr<Object> value){ return GenericObject<T>::Cast(value)->item; }
	static std::shared_ptr<GenericObject<T>> Cast(std::shared_ptr<Object> value)
	{
#ifdef _DEBUG
		std::shared_ptr<GenericObject<T>> obj = std::dynamic_pointer_cast<GenericObject<T>>(value);
		if (!obj)
		{
			throw std::exception("Attempting to access a wrong Generic Object in T& GetValue(std::shared_ptr<Object> value)");
		}
		return obj;
#else
		return std::static_pointer_cast<GenericObject<T>>(value);
#endif
	}
};

#endif //__Object__