#ifndef __EntityList__
#define __EntityList__

#include "Linker.h"

#include <string>
#include "ObjectEntity.h"
#include "CameraEntity.h"
#include "DrawSettingsEntity.h"


namespace ObjectEntities
{
	CommonDLL_API std::unordered_map<std::string, std::weak_ptr<ObjectEntity>> GetAll();
	CommonDLL_API void Add(std::shared_ptr<ObjectEntity> objEntity);
	CommonDLL_API bool Find(const std::string& ID, std::weak_ptr<ObjectEntity>& returnObj);
	CommonDLL_API void Remove(const std::string& ID);
}

namespace CameraEntities
{
	CommonDLL_API std::unordered_map<std::string, std::weak_ptr<CameraEntity>> GetAll();
	CommonDLL_API void Add(std::shared_ptr<CameraEntity> objEntity);
	CommonDLL_API bool Find(const std::string& ID, std::weak_ptr<CameraEntity>& returnObj);
	CommonDLL_API void Remove(const std::string& ID);
}

namespace DrawSettingsEntities
{
	CommonDLL_API std::unordered_map<std::string, std::weak_ptr<DrawSettingsEntity>> GetAll();
	CommonDLL_API void Add(std::shared_ptr<DrawSettingsEntity> objEntity);
	CommonDLL_API bool Find(const std::string& ID, std::weak_ptr<DrawSettingsEntity>& returnObj);
	CommonDLL_API void Remove(const std::string& ID);
}

#endif //__EntityList__