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

		Singelton(){}
		Singelton(const Singelton& cs) {}
		//Singelton& operator = (const Singelton& cs) {return cs;}

	public:
		static CWrappedClass& GetInstance()
		{
			if (ms_instance == 0)
				ms_instance = new CWrappedClass;
			return *ms_instance;
		}
	};

	template <class CWrappedClass>
	CWrappedClass* Singelton<CWrappedClass>::ms_instance = 0;
}

#endif //__Singelton___