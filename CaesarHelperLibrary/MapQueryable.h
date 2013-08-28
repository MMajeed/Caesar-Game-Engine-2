#ifndef __Querable__
#define __Querable__

#include <map>
#include <iterator>

namespace CHL
{
	template<typename key, typename value>
	class MapQuerable
	{
	public:
		MapQuerable(){}
		MapQuerable(std::map<key, value> input){ this->All = input; } 

		// Accepts a lambda function that takes a T
		// as paramter and returns bool if wants it or not. Check unit test for example
		// It then goes through the list and returns you everyitem that returned true
		template<typename lambdaFunc>
		MapQuerable<key, value> Where(const lambdaFunc& w)
		{
			std::map<key, value> whereVecObjects;

			for(auto iterObject = this->All.begin();
				iterObject != this->All.end();
				++iterObject)
			{
				bool add = w(*iterObject);
				if(add == true)
				{
					whereVecObjects[iterObject->first] = iterObject->second;
				}
			}

			MapQuerable<key, value> whereQuerableObject(whereVecObjects);

			return whereQuerableObject;
		}
		
		// Goes through each item in the list and perform the func on it
		// Check unit test for example
		template<typename lambdaFunc>
		MapQuerable<key, value> ForEach(const lambdaFunc& w)
		{
			for(auto iterObject = this->All.begin();
				iterObject != this->All.end();
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
		bool FirstOrDefault(const lambdaFunc& w, std::pair<key, value>& returnType)
		{

			for(auto iterObject = this->All.begin();
				iterObject != this->All.end();
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
		typename std::map<key, value>::iterator begin()
		{
			return this->All.begin();
		}

		// returns the emd of the iterator
		typename std::map<key, value>::iterator end()
		{
			return this->All.end();
		}

		// Gets you the value at that position
		value operator[](key loc)
		{
			return All[loc];
		}

		// Gets you the value at that position
		std::pair<key, value> find(key loc)
		{
			return All.find(loc);
		}

		std::map<key, value> All;
	};
}

#endif //__Querable__