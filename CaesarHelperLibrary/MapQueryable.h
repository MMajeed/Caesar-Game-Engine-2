#ifndef __MapQueryable__
#define __MapQueryable__

#include <hash_map>
#include <iterator>

namespace CHL
{
	template<typename T1, typename T2>
	class MapQueryable : public std::hash_map<T1, T2>
	{
	public:
		MapQueryable(){}

		// Accepts a lambda function that takes a T
		// as paramter and returns bool if wants it or not. Check unit test for example
		// It then goes through the list and returns you everyitem that returned true
		template<typename lambdaFunc>
		MapQueryable<T1, T2> Where(const lambdaFunc& w) const
		{
			std::hash_map<T1, T2> whereVecObjects;

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

			MapQueryable<T> whereQuerableObject(whereVecObjects);

			return whereQuerableObject;
		}
		
		// Goes through each item in the list and perform the func on it
		template<typename lambdaFunc>
		MapQueryable<T1, T2> ForEach(const lambdaFunc& w) const
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
		MapQueryable<T1, T2> ForEach(const lambdaFunc& w)
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
		bool FirstOrDefault(const lambdaFunc& w, std::pair<T1, T2>& returnType) const
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

#endif //__MapQueryable__