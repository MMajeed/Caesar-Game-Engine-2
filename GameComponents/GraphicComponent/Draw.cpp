#include "Draw.h"

#include "GraphicManager.h"
#include "ResourceManager.h"
#include "Rasterizer.h"

namespace Draw
{
	std::shared_ptr<VertexShader> GetVertexShader(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicObjectEntity> object)
	{
		std::shared_ptr<VertexShader> returnValue;

		if(camera->GetVertexShaderState() == CameraEntity::CAMERA_SHADER_TYPE::FORCE)
		{
			returnValue = camera->GetVertexShader();
		}
		else if(camera->GetVertexShaderState() == CameraEntity::CAMERA_SHADER_TYPE::DEFAULT)
		{
			returnValue = object->GetVertexShader();

			if(returnValue == false)
			{
				returnValue = camera->GetVertexShader();
			}
		}

		return returnValue;
	}
	std::shared_ptr<GeometryShader> GetGeometryShader(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicObjectEntity> object)
	{
		std::shared_ptr<GeometryShader> returnValue = object->GetGeometryShader();

		return returnValue;
	}
	std::shared_ptr<PixelShader> GetPixelShader(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicObjectEntity> object)
	{
		std::shared_ptr<PixelShader> returnValue;

		if(camera->GetPixelShaderState() == CameraEntity::CAMERA_SHADER_TYPE::FORCE)
		{
			returnValue = camera->GetPixelShader();
		}
		else if(camera->GetPixelShaderState() == CameraEntity::CAMERA_SHADER_TYPE::DEFAULT)
		{
			returnValue = object->GetPixelShader();

			if(returnValue == false)
			{
				returnValue = camera->GetPixelShader();
			}
		}

		return returnValue;
	}
	std::shared_ptr<GraphicModel> GetGraphicModel(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicObjectEntity> object)
	{
		std::shared_ptr<GraphicModel> returnValue = object->GetGraphicModel();

		return returnValue;
	}

	void Setup(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicObjectEntity> object)
	{
		auto& d3dStuff = GraphicManager::GetInstance().D3DStuff;
		ID3D11DeviceContext* pImmediateContext = d3dStuff.pImmediateContext;

		std::shared_ptr<VertexShader> vertexShader = GetVertexShader(camera, object);
		std::shared_ptr<GeometryShader> geometryShader = GetGeometryShader(camera, object);
		std::shared_ptr<PixelShader> pixelShader = GetPixelShader(camera, object);
		std::shared_ptr<GraphicModel> model = GetGraphicModel(camera, object);

		if(vertexShader == false){ return; }
		if(pixelShader == false){ return; }
		if(model == false){ return; }

		if(object->GetDepth() == true){ pImmediateContext->OMSetDepthStencilState(d3dStuff.pDepthStencilState, 1); }
		else	{ pImmediateContext->OMSetDepthStencilState(d3dStuff.pDepthDisabledStencilState, 1); }

		vertexShader->Setup(camera, object);
		if(geometryShader)	{ geometryShader->Setup(camera, object); }
		else				{ pImmediateContext->GSSetConstantBuffers(0, 0, nullptr); }
		pixelShader->Setup(camera, object);
		model->Setup(camera, object);

		Rasterizer::Setup(camera, object);

		pImmediateContext->DrawIndexed(model->GetNumberFaces(), 0, 0);
	}
};