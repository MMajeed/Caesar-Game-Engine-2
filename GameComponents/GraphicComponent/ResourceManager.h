#ifndef __ResourceManager__
#define __ResourceManager__

#include "Linker.h"
#include <hash_map>
#include <string>
#include "GraphicModel.h"
#include "BasicTexture.h"
#include "ScreenCapture.h"
#include "VertexShader.h"
#include "GeometryShader.h"
#include "PixelShader.h"

namespace ResourceManager
{
	template <typename T>
	class Resource
	{
	public:
		std::hash_map<std::string, std::shared_ptr<T>> objList;

		void Insert(const std::string& ID, std::shared_ptr<T> obj)
		{
			this->objList[ID] = obj;
		}
		std::shared_ptr<T> Find(const std::string& ID)
		{
			std::shared_ptr<T> returnValue;

			auto iter = this->objList.find(ID);
			if(iter != this->objList.end())
			{
				returnValue = iter->second;
			}

			return returnValue;
		}
		void Remove(const std::string& ID)
		{
			auto iter = this->objList.find(ID);
			if(iter != this->objList.end())
			{
				this->objList.erase(iter);
			}
		}
		const std::hash_map<std::string, std::shared_ptr<T>>& All()
		{
			return this->objList;
		}
	};

	extern GraphicComponentDLL_API ResourceManager::Resource<GraphicModel>		GraphicModelList;
	extern GraphicComponentDLL_API ResourceManager::Resource<BasicTexture>		TextureList;
	extern GraphicComponentDLL_API ResourceManager::Resource<ScreenCapture>		ScreenCaptureList;
	extern GraphicComponentDLL_API ResourceManager::Resource<VertexShader>		VertexShaderList;
	extern GraphicComponentDLL_API ResourceManager::Resource<GeometryShader>	GeometryShaderList;
	extern GraphicComponentDLL_API ResourceManager::Resource<PixelShader>		PixelShaderList;

};

#endif //__ResourceManager__