#include "Rasterizer.h"

#include "GraphicCameraEntity.h"
#include "GraphicObjectEntity.h"

#include "GraphicManager.h"
#include "COMSharedPtr.h"
#include <sstream>
#include <D3D11.h>
#include <hash_map>

namespace Rasterizer
{
	static std::hash_map<std::string, COMSharedPtr<ID3D11RasterizerState>> RasterizerList;

	COMSharedPtr<ID3D11RasterizerState> GetRasterizer(const GraphicCameraEntity& camera, const GraphicObjectEntity& object)
	{
		COMSharedPtr<ID3D11RasterizerState> returnValue;

		D3D11_FILL_MODE fillMode = object.GetFillMode();
		D3D11_CULL_MODE cullMode = object.GetCullMode();

		std::stringstream ss;
		ss << fillMode << cullMode;

		auto iter = RasterizerList.find(ss.str());
		if(iter != RasterizerList.end())
		{
			returnValue = iter->second;
		}
		else
		{
			auto& graphicD3D = GraphicManager::GetInstance().D3DStuff;

			D3D11_RASTERIZER_DESC RSDesc;
			memset(&RSDesc, 0, sizeof(D3D11_RASTERIZER_DESC));
			RSDesc.FillMode = fillMode;
			RSDesc.CullMode = cullMode;

			ID3D11RasterizerState* rs;
			HRESULT hr = graphicD3D.pd3dDevice->CreateRasterizerState(&RSDesc, &rs);
			if(FAILED(hr)){	Logger::LogError("ErrorException: Can't create rasterizer state");	}

			RasterizerList[ss.str()] = rs;
			returnValue = RasterizerList[ss.str()];
		}

		return returnValue;
	}

	void Setup(const GraphicCameraEntity& camera, const GraphicObjectEntity& object)
	{
		auto& graphicD3D = GraphicManager::GetInstance().D3DStuff;

		COMSharedPtr<ID3D11RasterizerState> rasterizer = GetRasterizer(camera, object);
		ID3D11RasterizerState* rs = rasterizer;
		graphicD3D.pImmediateContext->RSSetState(rs);
	}
};