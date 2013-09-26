#include "GetInfoManager.h"

#include <ObjectManager.h>

Interface* GetInfoManager::GetComponent()
{
	return &ObjectManager::GetInstance();
}