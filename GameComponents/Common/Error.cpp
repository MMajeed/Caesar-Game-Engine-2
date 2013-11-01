#include "Error.h"

void Error::Check()
{
	if (eptr != std::exception_ptr())
	{
		std::rethrow_exception(eptr);
	}
}
void Error::SetError(std::exception_ptr inputEptr)
{
	this->eptr = inputEptr;
}