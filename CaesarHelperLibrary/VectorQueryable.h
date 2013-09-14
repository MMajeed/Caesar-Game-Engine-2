#ifndef __VectorQueryable__
#define __VectorQueryable__

#include <vector>
#include <iterator>

namespace CHL
{
	template<typename T>
	class VectorQueryable : public std::vector<T>
	{
	public:
		VectorQueryable(){}

		// Accepts a lambda function that takes a T
		// as paramter and returns bool if wants it or not. Check unit test for example
		// It then goes through the list and returns you everyitem that returned true
		template<typename lambdaFunc>
		VectorQueryable<T>Where(const lambdaFunc& w) const
		{
			std::vector<T> whereVecObjects;

			for(auto iterObject = this->cbegin();
				iterObject != this->cend();
				++iterObject)
			{
				bool add = w(*iterObject);
				if(add == true)
				{
					whereVecObjects.push_back(*iterObject);
				}
			}

			VectorQueryable<T>whereQuerableObject(whereVecObjects);

			return whereQuerableObject;
		}
		
		// Goes through each item in the list and perform the func on it
		template<typename lambdaFunc>
		VectorQueryable<T>ForEach(const lambdaFunc& w) const
		{
			for(auto iterObject = this->cbegin();
				iterObject != this->cend();
				++iterObject)
			{
				w(*iterObject);
			}

			return *this;
		}

		// Goes through each item in the list and perform the func on it
		template<typename lambdaFunc>
		VectorQueryable<T>ForEach(const lambdaFunc& w)
		{
			for(auto iterObject = this->begin();
				iterObject != this->end();
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
		bool FirstOrDefault(const lambdaFunc& w, T& returnType) const
		{

			for(auto iterObject = this->cbegin();
				iterObject != this->cend();
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
	};
}

#endif //__VectorQueryable__
