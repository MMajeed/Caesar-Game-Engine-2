#ifndef __Vector__
#define __Vector__

#include <array>
#include <algorithm>

namespace CML
{
	template<typename Type, unsigned int ArraySize>
	class Vector
	{
	public:
		std::array<Type, ArraySize> arr;

		Vector(){ std::fill(arr.begin(), arr.end(), 0); }

		Vector(std::initializer_list<Type> args)
		{
			if(args.size() == ArraySize)
			{
				std::copy(args.begin(), args.end(), this->arr.begin());
			}
			else if(args.size() < ArraySize)
			{
				std::copy(args.begin(), args.end(), this->arr.begin());
				std::fill(arr.begin() + args.size(), arr.end(), 0); 
			}
			else
			{
				auto properEnd = args.begin() + ArraySize;
				std::copy(args.begin(), properEnd, this->arr.begin());
			}
		}
		Vector& operator=(std::initializer_list<Type> args)
		{
			std::copy(args.begin(), args.end(), this->arr.begin());
			if(args.size() < ArraySize){ std::fill(arr.begin() + args.size(), arr.end(), 0); }
			return *this;
		}

		template <typename T, int S> 
		Vector(const Vector<T, S>& rhs)
		{
			for(std::size_t i = 0; i < S && i < ArraySize; ++i)
			{
				arr[i] = rhs[i];
			}
			for(std::size_t i = S; i < ArraySize; ++i)
			{
				arr[i] = 0;
			}
		}
		template <typename T, int S> 
		Vector& operator=(const Vector<T, S>& rhs)
		{
			for(std::size_t i = 0; i < S && i < ArraySize; ++i)
			{
				this->arr[i] = rhs[i];
			}
			for(std::size_t i = S; i < ArraySize; ++i)
			{
				this->arr[i] = 0;
			}
			return *this;
		}

		Vector(const Vector<Type, ArraySize>& rhs) = default;
		Vector& operator=(const Vector<Type, ArraySize>& other) = default;

		inline int Size(){ return ArraySize; }

		Type& operator()(unsigned int index){ return this->arr[index]; };
		Type operator()(unsigned int index) const { return this->arr[index]; };

		Type& operator[](unsigned int index){ return this->arr[index]; };
		Type operator[](unsigned int index) const { return this->arr[index]; };
	};

	typedef Vector<double, 2> Vec2;
	typedef Vector<double, 3> Vec3;
	typedef Vector<double, 4> Vec4;
};

#endif //__Vector__