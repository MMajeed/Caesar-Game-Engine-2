#ifndef __KeyStatuss__
#define __KeyStatuss__

class KeyStatus
{
public:
	enum class Status {Up = 0, Down = 1};

	KeyStatus();

	void UpdateStatus(Status status);

	void Update(double realTime);

	double duration;
	Status CurrentStatus;
};

#endif //__KeyStatuss__