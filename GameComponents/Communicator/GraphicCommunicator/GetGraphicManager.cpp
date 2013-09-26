#include "GetGraphicManager.h"

#include <GraphicManager.h>

Interface* GetGraphicManager::GetComponent()
{
	return &GraphicManager::GetInstance();
}