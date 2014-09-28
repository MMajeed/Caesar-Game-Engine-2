#include "Rasterizer.h"

#include "GraphicCameraEntity.h"
#include "GraphicDrawSettingsEntity.h"
#include "GraphicObjectEntity.h"

#include "GraphicManager.h"
#include "COMSharedPtr.h"
#include <sstream>
#include <D3D11.h>
#include <unordered_map>

namespace Rasterizer
{
	static std::unordered_map<unsigned int, COMSharedPtr<ID3D11RasterizerState>> RasterizerList;

	unsigned int GenerateValue(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicDrawSettingsEntity> drawSettings, std::shared_ptr<GraphicObjectEntity> object)
	{
		unsigned int value = 0;

		D3D11_FILL_MODE fillMode = object->GetFillMode();
		D3D11_CULL_MODE cullMode = object->GetCullMode();

		value += fillMode + 1;
		value += cullMode + 10;

		return value;
	}

	COMSharedPtr<ID3D11RasterizerState> GetRasterizer(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicDrawSettingsEntity> drawSettings, std::shared_ptr<GraphicObjectEntity> object)
	{
		COMSharedPtr<ID3D11RasterizerState> returnValue;

		unsigned int value = GenerateValue(camera, drawSettings, object);

		auto iter = RasterizerList.find(value);
		if(iter != RasterizerList.end())
		{
			returnValue = iter->second;
		}
		else
		{
			auto& graphicD3D = GraphicManager::GetInstance().D3DStuff;

			D3D11_RASTERIZER_DESC RSDesc;
			memset(&RSDesc, 0, sizeof(D3D11_RASTERIZER_DESC));
			RSDesc.FillMode = object->GetFillMode();
			RSDesc.CullMode = object->GetCullMode();

			ID3D11RasterizerState* rs;
			HRESULT hr = graphicD3D.pd3dDevice->CreateRasterizerState(&RSDesc, &rs);
			if(FAILED(hr)){	Logger::LogError("ErrorException: Can't create rasterizer state");	}

			RasterizerList[value] = rs;
			returnValue = RasterizerList[value];
		}

		return returnValue;
	}

	void Setup(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicDrawSettingsEntity> drawSettings, std::shared_ptr<GraphicObjectEntity> object)
	{
		auto& graphicD3D = GraphicManager::GetInstance().D3DStuff;

		COMSharedPtr<ID3D11RasterizerState> rasterizer = GetRasterizer(camera, drawSettings, object);
		ID3D11RasterizerState* rs = rasterizer;
		graphicD3D.pImmediateContext->RSSetState(rs);
	}
};