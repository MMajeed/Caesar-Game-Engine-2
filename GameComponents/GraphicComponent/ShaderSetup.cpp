#include "ShaderSetup.h"

#include "VertexShader.h"
#include "GeometryShader.h"
#include "PixelShader.h"
#include "GraphicManager.h"
#include "ResourceManager.h"
#include "VSDefaultVS.h"
#include "PSDefaultPS.h"

namespace ShaderSetup
{
	std::shared_ptr<VertexShader> DefaultVertexShader()
	{
		static std::shared_ptr<VertexShader> d;
		if(d == false)
		{
			d = VertexShader::Spawn(VSDefaultVS);
		}
		return d;
	}
	std::shared_ptr<PixelShader> DefaultPixelShader()
	{
		static std::shared_ptr<PixelShader> d;
		if(d == false)
		{
			d = PixelShader::Spawn(PSDefaultPS);
		}
		return d;
	}
	
	void SetupVertexShader(std::string ID, std::shared_ptr<ObjectEntity> object, const SceneInfo& si)
	{
		std::shared_ptr<VertexShader> vertexShaderToUse;

		vertexShaderToUse = ResourceManager::VertexShaderList.Find(ID);

		if(vertexShaderToUse == false) // if we didn't find it
		{
			vertexShaderToUse = DefaultVertexShader(); // set it to default
		}

		vertexShaderToUse->Setup(object, si);
	}
	void SetupGeometryShader(std::string ID, std::shared_ptr<ObjectEntity> object, const SceneInfo& si)
	{
		std::shared_ptr<GeometryShader> gometryShaderToUse = ResourceManager::GeometryShaderList.Find(ID);

		if(gometryShaderToUse) // if we found it
		{
			gometryShaderToUse->Setup(object, si); // run it
		}
		else // Otherwise set it to null
		{
			auto& graphicD3D = GraphicManager::GetInstance().D3DStuff;
			graphicD3D.pImmediateContext->GSSetShader(NULL, NULL, 0);
		}
	}
	void SetupPixelShader(std::string ID, std::shared_ptr<ObjectEntity> object, const SceneInfo& si)
	{
		std::shared_ptr<PixelShader> pixelShaderToUse;

		pixelShaderToUse = ResourceManager::PixelShaderList.Find(ID);

		if(pixelShaderToUse == false) // if we didn't find it
		{
			pixelShaderToUse = DefaultPixelShader(); // set it to default
		}

		pixelShaderToUse->Setup(object, si);
	}
};

