#include "Draw.h"

#include "GraphicManager.h"
#include "Resource.h"
#include "Rasterizer.h"

namespace Draw
{
	std::shared_ptr<VertexShader> GetVertexShader(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicDrawSettingsEntity> drawSettings, std::shared_ptr<GraphicObjectEntity> object)
	{
		std::shared_ptr<VertexShader> returnValue;

		if(drawSettings->GetVertexShaderState() == DrawSettingsEntity::DRAWSETTINGS_TYPE::FORCE)
		{
			returnValue = drawSettings->GetVertexShader();
		}
		else if(drawSettings->GetVertexShaderState() == DrawSettingsEntity::DRAWSETTINGS_TYPE::DEFAULT)
		{
			returnValue = object->GetVertexShader();

			if(returnValue == false)
			{
				returnValue = drawSettings->GetVertexShader();
			}
		}

		return returnValue;
	}
	std::shared_ptr<GeometryShader> GetGeometryShader(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicDrawSettingsEntity> drawSettings, std::shared_ptr<GraphicObjectEntity> object)
	{
		std::shared_ptr<GeometryShader> returnValue = object->GetGeometryShader();

		return returnValue;
	}
	std::shared_ptr<PixelShader> GetPixelShader(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicDrawSettingsEntity> drawSettings, std::shared_ptr<GraphicObjectEntity> object)
	{
		std::shared_ptr<PixelShader> returnValue;

		if(drawSettings->GetPixelShaderState() == DrawSettingsEntity::DRAWSETTINGS_TYPE::FORCE)
		{
			returnValue = drawSettings->GetPixelShader();
		}
		else if(drawSettings->GetPixelShaderState() == DrawSettingsEntity::DRAWSETTINGS_TYPE::DEFAULT)
		{
			returnValue = object->GetPixelShader();

			if(returnValue == false)
			{
				returnValue = drawSettings->GetPixelShader();
			}
		}

		return returnValue;
	}
	std::shared_ptr<GraphicModel> GetGraphicModel(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicDrawSettingsEntity> drawSettings, std::shared_ptr<GraphicObjectEntity> object)
	{
		std::shared_ptr<GraphicModel> returnValue = object->GetGraphicModel();

		return returnValue;
	}

	void Setup(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicDrawSettingsEntity> drawSettings, std::shared_ptr<GraphicObjectEntity> object)
	{
		auto& d3dStuff = Resource::D3DStuff;
		ID3D11DeviceContext* pImmediateContext = d3dStuff.pImmediateContext;

		std::shared_ptr<VertexShader> vertexShader = GetVertexShader(camera, drawSettings, object);
		std::shared_ptr<GeometryShader> geometryShader = GetGeometryShader(camera, drawSettings, object);
		std::shared_ptr<PixelShader> pixelShader = GetPixelShader(camera, drawSettings, object);
		std::shared_ptr<GraphicModel> model = GetGraphicModel(camera, drawSettings, object);

		if(vertexShader == false){ return; }
		if(pixelShader == false){ return; }
		if(model == false){ return; }

		if(object->GetDepth() == true){ pImmediateContext->OMSetDepthStencilState(d3dStuff.pDepthStencilState, 1); }
		else	{ pImmediateContext->OMSetDepthStencilState(d3dStuff.pDepthDisabledStencilState, 1); }

		vertexShader->Setup(camera, drawSettings, object);
		if(geometryShader)	{ geometryShader->Setup(camera, drawSettings, object); }
		else				{ pImmediateContext->GSSetConstantBuffers(0, 0, nullptr); }
		pixelShader->Setup(camera, drawSettings, object);
		model->Setup(camera, drawSettings, object);

		Rasterizer::Setup(camera, drawSettings, object);

		pImmediateContext->DrawIndexed(model->GetNumberFaces(), 0, 0);
	}
};