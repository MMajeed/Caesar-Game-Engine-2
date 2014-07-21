#ifndef __Entity__
#define __Entity__

#include "Linker.h"

#include <string>
#include <memory>
#include <mutex>

class CommonDLL_API Entity
{
protected:
	Entity();
	Entity(const Entity& c);
	Entity& operator=(const Entity&) = delete;

	std::mutex metux;

private:	std::string ID;
public:		std::string GetID();

public:

	virtual std::shared_ptr<Entity> Clone() = 0;
	
	virtual ~Entity(){}
};

typedef std::shared_ptr<Entity> SP_INFO;

#endif //__Entity__