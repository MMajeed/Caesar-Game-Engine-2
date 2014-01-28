#ifndef __CMLToEigen__
#define __CMLToEigen__

#include "Vector.h"
#include "Matrix.h"
#include <Eigen\Dense>

namespace CML
{
	template<typename Type, unsigned int row, unsigned int col>
	CML::Matrix4x4 ConvertMatrix(const Eigen::Matrix<Type, row, col>& inputValue)
	{
		CML::Matrix4x4 returnValue;
		for(unsigned int x = 0; x < row; ++x)
		{
			for(unsigned int y = 0; y < col; ++y)
			{
				returnValue(x, y) = inputValue(x, y);
			}
		}
		return returnValue;
	}
	template<typename Type, unsigned int row, unsigned int col>
	Eigen::Matrix<Type, row, col> ConvertMatrix(const CML::Matrix4x4& inputValue)
	{
		Eigen::Matrix<Type, row, col> returnValue;
		for(unsigned int x = 0; x < row; ++x)
		{
			for(unsigned int y = 0; y < col; ++y)
			{
				returnValue(x, y) = inputValue(x, y);
			}
		}
		return returnValue;
	}

	template<typename Type, unsigned int row>
	Eigen::Matrix<Type, row, 1> ConvertVec(const CML::Vector<Type, row>& inputValue)
	{
		Eigen::Matrix<Type, row, 1> returnValue;
		for(unsigned int x = 0; x < row; ++x)
		{
			returnValue(x) = inputValue(x);
		}
		return returnValue;
	}
	template<typename Type, unsigned int row>
	CML::Vector<Type, row> ConvertVec(const Eigen::Matrix<Type, row, 1>& inputValue)
	{
		CML::Vector<Type, row> returnValue;
		for(unsigned int x = 0; x < row; ++x)
		{
			returnValue(x) = inputValue(x);
		}
		return returnValue;
	}
};

#endif //__CMLToEigen__