#ifndef __Matrix__
#define __Matrix__

#include <array>
#include <algorithm>
#include "Vector.h"

namespace CML
{
	template<typename Type, unsigned int FArraySize, unsigned int SArraySize>
	class Matrix
	{
		public:
		std::array<Vector<Type, SArraySize>, FArraySize> mat;
		Matrix()
		{
			for(unsigned int i = 0; i < FArraySize; ++i)
			{
				for(unsigned int x = 0; x < SArraySize; ++x)
				{
					if(i != x){ mat[i][x] = 0; }
					else{ mat[i][x] = 1; }
				}
			}
		}
		template <typename T, unsigned int  FS, unsigned int SS>
		Matrix(const Matrix<T, FS, SS>& rhs)
		{
			for(std::size_t i = 0; i < FS && i < FArraySize; ++i)
			{
				for(std::size_t x = 0; x < SS && x < SArraySize; ++x)
				{
					mat[i][x] = rhs(i, x);
				}
				for(std::size_t x = SS; x < SArraySize; ++x)
				{
					mat[i][x] = 0.0;
				}
			}
			for(std::size_t i = FS; i < FArraySize; ++i)
			{
				for(std::size_t x = 0; x < SArraySize; ++x)
				{
					mat[i][x] = 0.0;
				}
			}
		}
		template <typename T, unsigned int  FS, unsigned int SS>
		const Matrix<Type, FArraySize, SArraySize>& operator=( const Matrix<T, FS, SS>& rhs )
		{
			for(std::size_t i = 0; i < FS && i < FArraySize; ++i)
			{
				std::copy(rhs[i].begin(), rhs[i].end(), this->mat[i].arr.begin());
				if(SS < SArraySize){ std::fill(this->mat[i].arr.begin() + SS, this->mat[i].arr.end(), 0); }
			}
			for(unsigned int i = FS; i < FArraySize; ++i)
			{
				std::fill(this->mat[i].arr.begin(), this->mat[i].arr.end(), 0);
			}

			return *this;
		}
		Matrix(std::initializer_list<std::initializer_list<Type>> args)
		{
			unsigned int i = 0;
			for(auto argsIter : args)
			{
				std::copy(argsIter.begin(), argsIter.end(), this->mat[i].arr.begin());
				if(argsIter.size() < SArraySize){ std::fill(this->mat[i].arr.begin() + argsIter.size(), this->mat[i].arr.end(), 0); }
				++i;
			}
			for(unsigned int i = args.size(); i < FArraySize; ++i)
			{
				std::fill(this->mat[i].arr.begin(), this->mat[i].arr.end(), 0);
			}
		}
		Matrix& operator=( std::initializer_list<std::initializer_list<Type>> args )
		{
			unsigned int i = 0;
			for(auto argsIter : args)
			{
				std::copy(argsIter.begin(), argsIter.end(), this->mat[i].arr.begin());
				if(argsIter.size() < SArraySize){ std::fill(this->mat[i].arr.begin() + argsIter.size(), this->mat[i].arr.end(), 0); }
				++i;
			}
			for(unsigned int i = args.size(); i < FArraySize; ++i)
			{
				std::fill(this->mat[i].arr.begin(), this->mat[i].arr.end(), 0);
			}
			return *this;
		}

		inline unsigned int FirstArraySize(){ return FArraySize; }
		inline unsigned int SecondArraySize(){ return SArraySize; }
		Type& operator()(unsigned int fIndex, unsigned int sIndex){ return this->mat[fIndex][sIndex]; }
		const Type operator()(unsigned int fIndex, unsigned int sIndex) const { return this->mat[fIndex][sIndex]; }
		Vector<Type, SArraySize>& operator[](unsigned int index){ return this->mat[index]; };
		const Vector<Type, SArraySize> operator[](unsigned int index) const { return this->mat[index]; };
	};

	typedef Matrix<double, 4, 4> Matrix4x4;
	typedef Matrix<double, 3, 3> Matrix3x3;

};

#endif //__Matrix__