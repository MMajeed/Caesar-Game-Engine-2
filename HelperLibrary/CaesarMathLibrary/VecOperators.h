#ifndef __VecMath__
#define __VecMath__

#include "Vector.h"

namespace CML
{
	template<typename Type, unsigned int ArraySize>
	Vector<Type, ArraySize> operator+(const Vector<Type, ArraySize>& rhs, const Vector<Type, ArraySize>& lhs)
	{
		Vector<Type, ArraySize> returnValue;
		for(unsigned int i = 0; i < ArraySize; ++i)
		{
			returnValue(i) = rhs(i) + lhs(i);
		}
		return returnValue;
	}
	template<typename Type, unsigned int ArraySize>
	Vector<Type, ArraySize> operator-(const Vector<Type, ArraySize>& rhs, const Vector<Type, ArraySize>& lhs)
	{
		Vector<Type, ArraySize> returnValue;
		for(unsigned int i = 0; i < ArraySize; ++i)
		{
			returnValue(i) = rhs(i) - lhs(i);
		}
		return returnValue;
	}
	template<typename Type, unsigned int ArraySize>
	Vector<Type, ArraySize> operator*(const Vector<Type, ArraySize>& rhs, const Vector<Type, ArraySize>& lhs)
	{
		Vector<Type, ArraySize> returnValue;
		for(unsigned int i = 0; i < ArraySize; ++i)
		{
			returnValue(i) = rhs(i) * lhs(i);
		}
		return returnValue;
	}
	template<typename Type, unsigned int ArraySize>
	Vector<Type, ArraySize> operator/(const Vector<Type, ArraySize>& rhs, const Vector<Type, ArraySize>& lhs)
	{
		Vector<Type, ArraySize> returnValue;
		for(unsigned int i = 0; i < ArraySize; ++i)
		{
			returnValue(i) = rhs(i) / lhs(i);
		}
		return returnValue;
	}

	template<typename Type, unsigned int ArraySize>
	Vector<Type, ArraySize> operator+(const Vector<Type, ArraySize>& rhs, double lhs)
	{
		Vector<Type, ArraySize> returnValue;
		for(unsigned int i = 0; i < ArraySize; ++i)
		{
			returnValue(i) = rhs(i) + lhs;
		}
		return returnValue;
	}
	template<typename Type, unsigned int ArraySize>
	Vector<Type, ArraySize> operator-(const Vector<Type, ArraySize>& rhs, double lhs)
	{
		Vector<Type, ArraySize> returnValue;
		for(unsigned int i = 0; i < ArraySize; ++i)
		{
			returnValue(i) = rhs(i) - lhs;
		}
		return returnValue;
	}
	template<typename Type, unsigned int ArraySize>
	Vector<Type, ArraySize> operator*(const Vector<Type, ArraySize>& rhs, double lhs)
	{
		Vector<Type, ArraySize> returnValue;
		for(unsigned int i = 0; i < ArraySize; ++i)
		{
			returnValue(i) = rhs(i) * lhs;
		}
		return returnValue;
	}
	template<typename Type, unsigned int ArraySize>
	Vector<Type, ArraySize> operator/(const Vector<Type, ArraySize>& rhs, double lhs)
	{
		Vector<Type, ArraySize> returnValue;
		for(unsigned int i = 0; i < ArraySize; ++i)
		{
			returnValue(i) = rhs(i) / lhs;
		}
		return returnValue;
	}
}

#endif //__Vec4Math__