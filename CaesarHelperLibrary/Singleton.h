#ifndef __Singelton___
#define __Singelton___

#include "Linker.h"

namespace CHL
{
	template <class CWrappedClass>
	class Singelton
	{
	protected:
		static CWrappedClass* ms_instance;
	private:
		Singelton(){}
		Singelton(const CSingleton& ) {}
		Singelton& operator = (const Singelton&) {}

	public:
		static CWrappedClass& GetInstance()
		{
			if (ms_instance == NULL)
				ms_instance = new CWrappedClass;
			return *ms_instance;
		}
	};

	template <class CWrappedClass>
	CWrappedClass* Singelton<CWrappedClass>::ms_instance = NULL;
}

#endif //__Singelton___