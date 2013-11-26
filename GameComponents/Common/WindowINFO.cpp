#include "WindowINFO.h"
#include "Keys.h"
#include <Windows.h>

std::shared_ptr<Object> WindowINFO::Get(const std::string& ID)
{
	std::shared_ptr<Object> returnValue;

	returnValue = INFO::Get(ID);
	if(!returnValue)
	{
			 if(ID == Keys::Window::WIDTH){ returnValue = GenericObj<int>::CreateNew(this->Width); }
		else if(ID == Keys::Window::HEIGHT){ returnValue = GenericObj<int>::CreateNew(this->Height); }
		//else if(ID == Keys::Window::HWND){ returnValue = GenericObj<HWND>::CreateNew(this->HWND); }
	}

	return returnValue;
}


void WindowINFO::Set(const std::string& ID, std::shared_ptr<Object> obj)
{
	INFO::Set(ID, obj);

		 if(ID == Keys::Window::WIDTH){ this->Width = GenericObj<int>::GetValue(obj); }
	else if(ID == Keys::Window::HEIGHT){ this->Height = GenericObj<int>::GetValue(obj); }
	//else if(ID == Keys::Window::HWND){ this->HWND = GenericObj<HWND>::GetValue(obj); }
}

std::shared_ptr<INFO> WindowINFO::Clone()
{
	return std::make_shared<WindowINFO>(*this);
}