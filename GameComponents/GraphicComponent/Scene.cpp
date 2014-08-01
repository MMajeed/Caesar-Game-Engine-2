#include "Scene.h"

#include "GraphicManager.h"
#include "ResourceManager.h"
#include <EntityList.h>

namespace Scene
{
	GraphicCameraEntity GetCamera(const std::string& ID)
	{
		GraphicCameraEntity returnValue;

		std::weak_ptr<CameraEntity> wpCE;
		if(CameraEntities::Find(ID, wpCE) == true){ returnValue = wpCE; }

		return returnValue;
	}
	std::hash_map<std::string, GraphicObjectEntity> GetAllObjectEntities()
	{
		std::hash_map<std::string, GraphicObjectEntity> returnValue;

		std::hash_map<std::string, std::weak_ptr<ObjectEntity>> ObjectEntityList = ObjectEntities::GetAll();
		returnValue.reserve(ObjectEntityList.size());
		for(auto iter = ObjectEntityList.begin(); iter != ObjectEntityList.end(); ++iter)
		{
			returnValue[iter->first] = GraphicObjectEntity(iter->second);
		}

		return returnValue;
	}

	void ClearScreen(const GraphicCameraEntity& Camera)
	{
		GraphicManager& graphic = GraphicManager::GetInstance();
		auto& d3dStuff = graphic.D3DStuff;

		// Clear the back buffer 
		auto c = Camera.GetClearColor();
		float ClearColor[4] = {c[0], c[1], c[2], c[3]};
		d3dStuff.pImmediateContext->ClearRenderTargetView(d3dStuff.pRenderTargetView, ClearColor);
		d3dStuff.pImmediateContext->ClearDepthStencilView(d3dStuff.pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	}
	void DrawObjects(const GraphicCameraEntity& Camera, std::hash_map<std::string, GraphicObjectEntity>& list)
	{
		ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().D3DStuff.pImmediateContext;

		std::vector<GraphicObjectEntity> objects = Camera.FilterInclusionList(list);
		for(const GraphicObjectEntity& object : objects)
		{
			object.Draw(Camera);
		}
	}
};