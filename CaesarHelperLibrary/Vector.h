#ifndef __Vector__
#define __Vector__

namespace CHL
{
	template<typename Type, unsigned int ArraySize>
	class Vector
	{
	public:
		Type vecArray[ArraySize];
		Vector(){ memset(&this->vecArray, 0, ArraySize * sizeof(Type));	}

		template <typename T, int S> 
		Vector(const Vector<T, S>& rhs)
		{
			for(std::size_t i = 0; i < S && i < ArraySize; ++i)
			{
				vecArray[i] = rhs[i];
			}
			for(std::size_t i = S; i < ArraySize; ++i)
			{
				vecArray[i] = 0;
			}
		}
		template <typename T, int S> 
		const Vector<Type, ArraySize>& operator=(const Vector<T, S>& rhs)
		{
			Vector<Type, ArraySize> returnValue;

			for(std::size_t i = 0; i < S && i < ArraySize; ++i)
			{
				returnValue[i] = rhs[i];
			}
			for(std::size_t i = S; i < ArraySize; ++i)
			{
				vecArray[i] = 0;
			}

			return returnValue;
		}

		inline int Size(){ return ArraySize; }
		Type& operator()(unsigned int index){ return this->vecArray[index]; };
		Type operator()(unsigned int index) const { return this->vecArray[index]; };
		Type& operator[](unsigned int index){ return this->vecArray[index]; };
		Type operator[](unsigned int index) const { return this->vecArray[index]; };
	};

	typedef Vector<double, 2> Vec2;
	typedef Vector<double, 3> Vec3;
	typedef Vector<double, 4> Vec4;
};

#endif //__Vector__