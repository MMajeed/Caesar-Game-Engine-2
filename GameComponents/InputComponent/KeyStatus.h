#ifndef __KeyStatuss__
#define __KeyStatuss__

#include "Linker.h"

class KeyStatus
{
public:
	enum class Status { KeyUp = 0, KeyDown = 1 };

	KeyStatus();

	void UpdateStatus(Status status);

	void Update(double realTime);

	double duration;
	Status CurrentStatus;
};

#endif //__KeyStatuss__