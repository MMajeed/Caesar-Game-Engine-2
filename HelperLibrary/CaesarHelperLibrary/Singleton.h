#ifndef __Singleton___
#define __Singleton___

#include "Linker.h"

#include <memory>

namespace CHL
{
	template <class CWrappedClass>
	class Singleton
	{
	protected:
		static std::shared_ptr<CWrappedClass> ms_instance;

		Singleton(){}
		Singleton(const Singleton& cs) {}
		const Singleton& operator = (const Singleton& cs) { return cs; }

	public:
		static CWrappedClass& GetInstance()
		{
			if (ms_instance == 0)
				ms_instance = std::shared_ptr<CWrappedClass>(new CWrappedClass);
			return *ms_instance;
		}
		static std::shared_ptr<CWrappedClass> GetPointer()
		{
			if(ms_instance == 0)
				ms_instance = std::shared_ptr<CWrappedClass>(new CWrappedClass);
			return ms_instance;
		}
	};

	template <class CWrappedClass>
	std::shared_ptr<CWrappedClass> Singleton<CWrappedClass>::ms_instance = 0;
}

#endif //__Singleton___