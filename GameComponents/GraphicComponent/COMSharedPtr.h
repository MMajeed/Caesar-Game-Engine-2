#ifndef __COMSharedPtr__
#define __COMSharedPtr__

#include <memory>
#include <iostream>

template <typename T>
struct ComReleaser
{
	void operator()(T* p) const
	{
		if(p)
		{ 
			p->Release(); 
		}
	}
};

template <typename T, typename Deleted = ComReleaser<T>>
class COMSharedPtr
{
public:
	std::shared_ptr<T> ptr;

	COMSharedPtr() = default;
	COMSharedPtr(T* ptr) : ptr(ptr, Deleted()){}

	T& operator*() const{ return *ptr; }
	std::shared_ptr<T> operator->() const{ return ptr; }
	operator T*(){ return ptr.get(); }

	void reset(){ ptr.reset(); }

	T* get() const{ return ptr.get(); }

	operator bool() const{ return (bool)ptr; }
};


#endif //__COMSharedPtr__