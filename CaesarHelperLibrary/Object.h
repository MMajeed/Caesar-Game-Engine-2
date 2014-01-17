#ifndef __Object__
#define __Object__

#include "Linker.h"

#include <memory>
#include "Logger.h"

class Object
{
public:
	virtual std::shared_ptr<Object> Clone() const = 0;
};

template<typename T>
class GenericObj : public Object
{
public:
	T item;
	GenericObj(T copy) : item(copy){}
	operator T() const{ return this->item; }
	operator T&(){ return this->item; }
	T GetValue()const{ return this->item; }
	T& GetValue(){ return this->item; }
	std::shared_ptr<Object> Clone()  const{ return std::make_shared<GenericObj<T>>(*this); }

	static std::shared_ptr<GenericObj<T>> CreateNew(const T& value){ return std::make_shared<GenericObj<T>>(value); }
	static T& GetValue(const std::shared_ptr<Object>& value){ return GenericObj<T>::Cast(value)->item; }
	static std::shared_ptr<GenericObj<T>> Cast(const std::shared_ptr<Object>& value)
	{
#ifdef _DEBUG
		std::shared_ptr<GenericObj<T>> obj = std::dynamic_pointer_cast<GenericObj<T>>(value);
		if (!obj)
		{
			Logger::LogError("Attempting to access a wrong Generic Object in T& GetValue(std::shared_ptr<Object> value)");
		}
		return obj;
#else
		return std::static_pointer_cast<GenericObj<T>>(value);
#endif
	}
};

#endif //__Object__