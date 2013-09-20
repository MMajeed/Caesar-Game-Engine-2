#ifndef __Queryable__
#define __Queryable__

#include <vector>
#include <hash_map>
#include <iterator>
#include <algorithm>

namespace CHL
{
	template<typename T>
	class Queryable : public T
	{
	public:
		Queryable(){}

		// Accepts a lambda function that takes a T
		// as paramter and returns bool if wants it or not.
		// It then goes through the list and returns you everyitem that returned true
		template<typename lambdaFunc>
		Queryable<T> Where(const lambdaFunc& w) const
		{
			Queryable<T> whereObject;

			for(auto iterObject = this->cbegin();
				iterObject != this->cend();
				++iterObject)
			{
				bool add = w(iterObject);
				if(add == true)
				{
					whereObject.insert(whereObject.end(), *iterObject);
				}
			}

			return whereObject;
		}
		
		// Goes through each item in the list and perform the func on it
		template<typename lambdaFunc>
		Queryable<T> ForEach(const lambdaFunc& w) const
		{
			for(auto iterObject = this->cbegin();
				iterObject != this->cend();
				++iterObject)
			{
				w(iterObject);
			}

			return *this;
		}
		template<typename lambdaFunc>
		Queryable<T> ForEach(const lambdaFunc& w)
		{
			for(auto iterObject = this->begin();
				iterObject != this->end();
				++iterObject)
			{
				w(iterObject);
			}

			return *this;
		}

		// Returns the first iterator that the paramter function returns true
		template<typename lambdaFunc>
		typename T::const_iterator First(const lambdaFunc& w) const
		{
			for(auto iterObject = this->cbegin();
				iterObject != this->cend();
				++iterObject)
			{
				bool add = w(iterObject);
				if(add == true)
				{
					return iterObject;
				}
			}
			return this->cend();
		}
		template<typename lambdaFunc>
		typename T::iterator First(const lambdaFunc& w)
		{
			for(auto iterObject = this->begin();
				iterObject != this->end();
				++iterObject)
			{
				bool add = w(iterObject);
				if(add == true)
				{
					return iterObject;
				}
			}
			return this->end();
		}
	};

	template<typename T1>
	class VectorQueryable : public Queryable<std::vector<T1>>
	{
	public:
		VectorQueryable(){}
		VectorQueryable(typename std::vector<T1> vec)
		{
			this->resize(vec.size());
			std::copy(vec.begin(), vec.end(), this->begin()); 
		}
		VectorQueryable(typename Queryable<std::vector<T1>> vec)
		{
			this->resize(vec.size());
			std::copy(vec.begin(), vec.end(), this->begin()); 
		}
	};

	template<typename T1, typename T2>
	class MapQueryable : public Queryable<std::hash_map<T1, T2>>
	{
	public:
		MapQueryable(){}
		MapQueryable(typename std::hash_map<T1, T2> vec)
		{
			this->insert(vec.begin(), vec.end());
		}
		MapQueryable(typename Queryable<std::hash_map<T1, T2>> vec)
		{
			this->insert(vec.begin(), vec.end());
		}
	};

}

#endif //__Queryable__
