#ifndef __VecMath__
#define __VecMath__

#include "Vector.h"

namespace CHL
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
	Vector<Type, ArraySize> CrossProduct(const Vector<Type, ArraySize>& rhs, const Vector<Type, ArraySize>& lhs)
	{
		Vector<Type, ArraySize> returnValue;
		for(unsigned int i = 0; i < ArraySize; ++i)
		{
			unsigned int firstNext = i + 1;
			if(firstNext >= ArraySize){ firstNext -= ArraySize; }
			unsigned int secondNext = i + 2;
			if(secondNext >= ArraySize){ secondNext -= ArraySize; }
			returnValue(i) = (rhs(firstNext) * lhs(secondNext)) - (lhs(firstNext) * rhs(secondNext));
		}
		return returnValue;
	}

	template<typename Type, unsigned int ArraySize>
	Vector<Type, ArraySize> Normalize(const Vector<Type, ArraySize>& rhs)
	{
		Vector<Type, ArraySize> returnValue;

		Type length = 0;
		for(unsigned int i = 0; i < ArraySize; ++i)
		{
			length += rhs(i) * rhs(i);
		}
		if(length != 0)
		{
			Type reciprical = 1 / std::sqrt(length);
			for(unsigned int i = 0; i < ArraySize; ++i)
			{
				returnValue(i) = rhs(i) * reciprical;
			}
		}

		return returnValue;
	}

};

#endif //__Vec4Math__