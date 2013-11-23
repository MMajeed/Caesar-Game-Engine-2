#ifndef __Singleton___
#define __Singleton___

#include "Linker.h"

namespace CHL
{
	template <class CWrappedClass>
	class Singleton
	{
	protected:
		static CWrappedClass* ms_instance;

		Singleton(){}
		Singleton(const Singleton& cs) {}
		Singleton& operator = (const Singleton& cs) {return cs;}

	public:
		static CWrappedClass& GetInstance()
		{
			if (ms_instance == 0)
				ms_instance = new CWrappedClass;
			return *ms_instance;
		}
	};

	template <class CWrappedClass>
	CWrappedClass* Singleton<CWrappedClass>::ms_instance = 0;
}

#endif //__Singleton___