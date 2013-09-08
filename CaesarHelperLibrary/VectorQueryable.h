#ifndef __VectorQuerable__
#define __VectorQuerable__

#include <vector>
#include <iterator>

namespace CHL
{
	template<typename T>
	class VectorQuerable
	{
	public:
		VectorQuerable(){}
		VectorQuerable(std::vector<T> input){ this->All = input; } 
		//VectorQuerable(VectorQuerable<const T> input){ this->All = input; } 

		// Accepts a lambda function that takes a T
		// as paramter and returns bool if wants it or not. Check unit test for example
		// It then goes through the list and returns you everyitem that returned true
		template<typename lambdaFunc>
		VectorQuerable<T> Where(const lambdaFunc& w)
		{
			std::vector<T> whereVecObjects;

			for(std::vector<T>::iterator iterObject = this->All.cbegin();
				iterObject != this->All.cend();
				++iterObject)
			{
				bool add = w(*iterObject);
				if(add == true)
				{
					whereVecObjects.push_back(*iterObject);
				}
			}

			VectorQuerable<T> whereQuerableObject(whereVecObjects);

			return whereQuerableObject;
		}
		
		// Goes through each item in the list and perform the func on it
		// Check unit test for example
		template<typename lambdaFunc>
		VectorQuerable<T> ForEach(const lambdaFunc& w)
		{
			for(auto iterObject = this->All.cbegin();
				iterObject != this->All.cend();
				++iterObject)
			{
				w(*iterObject);
			}

			return *this;
		}

		// Accepts a lambda function that takes std::shared_ptr<SPObject>>
		// as paramter and returns bool if wants it or not. Check unit test for example
		// It returns the first value that returns true, but if it didn't value then it return false
		// So do check it before you use
		template<typename lambdaFunc>
		bool FirstOrDefault(const lambdaFunc& w, T& returnType)
		{

			for(auto iterObject = this->All.cbegin();
				iterObject != this->All.cend();
				++iterObject)
			{
				bool add = w(*iterObject);
				if(add == true)
				{
					returnType = *iterObject;
					return true;
				}
			}

			return false;
		}

		// Returns size
		std::size_t size()
		{
			return this->All.size();
		}

		// returns the begin of the iterator
		typename std::vector<T>::iterator begin()
		{
			return this->All.begin();
		}

		// returns the emd of the iterator
		typename std::vector<T>::iterator end()
		{
			return this->All.end();
		}

		// Gets you the value at that position
		T& operator[](std::size_t loc)
		{
			return All[loc];
		}

		// Gets you the value at that position
		const T& operator[](std::size_t loc) const
		{
			return All[loc];
		}

		void push_back(T object)
		{
			this->All.push_back(object);
		}

		std::vector<T> All;
	};
}

#endif //__VectorQuerable__