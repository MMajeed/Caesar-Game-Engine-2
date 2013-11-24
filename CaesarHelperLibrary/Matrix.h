#ifndef __Matrix__
#define __Matrix__

namespace CHL
{
	template<typename Type, unsigned int FArraySize, unsigned int SArraySize>
	class Matrix
	{
	public:
		Type arr[FArraySize][SArraySize];

		Matrix(){ memset(&this->arr, 0, ( sizeof(Type) * FArraySize * SArraySize ) );	}

		template <typename T, unsigned int  FS, unsigned int SS> 
		Matrix(const Matrix<T, FS, SS>& rhs)
		{
			for(std::size_t i = 0; i < FS && i < FArraySize; ++i)
			{
				for(std::size_t x = 0; x < SS && x < SArraySize; ++x)
				{
					arr[i][x] = rhs(i, x);
				}
				for(std::size_t x = SS; x < SArraySize; ++x)
				{
					arr[i][x] = 0.0;
				}
			}
			for(std::size_t i = FS; i < FArraySize; ++i)
			{
				for(std::size_t x = 0; x < SArraySize; ++x)
				{
					arr[i][x] = 0.0;
				}
			}
		}
		template <typename T, unsigned int  FS, unsigned int SS> 
		const Matrix<Type, FArraySize, SArraySize>& operator=(const Matrix<T, FS, SS>& rhs)
		{
			Matrix<Type, FArraySize, SArraySize> returnValue;

			for(std::size_t i = 0; i < FS && i < FArraySize; ++i)
			{
				for(std::size_t x = 0; x < SS && x < SArraySize; ++x)
				{
					returnValue(i, x) = rhs(i, x);
				}
				for(std::size_t x = SS; x < SArraySize; ++x)
				{
					returnValue(i, x) = 0.0;
				}
			}
			for(std::size_t i = FS; i < FArraySize; ++i)
			{
				for(std::size_t x = 0; x < SArraySize; ++x)
				{
					returnValue(i, x) = 0.0;
				}
			}

			return returnValue;
		}

		inline unsigned int FirstArraySize(){ return FArraySize; }
		inline unsigned int SecondArraySize(){ return SArraySize; }
		Type& operator()(unsigned int fIndex, unsigned int sIndex){ return this->arr[fIndex][sIndex]; }
		Type operator()(unsigned int fIndex, unsigned int sIndex) const { return this->arr[fIndex][sIndex]; }
		Type* operator[](unsigned int index){ return this->arr[index]; };
		const Type* operator[](unsigned int index) const { return this->arr[index]; };
	};

	typedef Matrix<double, 4, 4> Matrix4x4;
	typedef Matrix<double, 3, 3> Matrix3x3;

};

#endif //__Matrix__