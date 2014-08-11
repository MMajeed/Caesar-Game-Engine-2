#include "Scene.h"

#include "GraphicManager.h"
#include "ResourceManager.h"
#include "Rasterizer.h"
#include "Draw.h"
#include <EntityList.h>
#include <set>

namespace Scene
{
	std::shared_ptr<GraphicCameraEntity> GetCamera(const std::string& ID, unsigned int width, unsigned int height)
	{
		std::weak_ptr<CameraEntity> wpCE;
		if(CameraEntities::Find(ID, wpCE) == true){ return std::make_shared<GraphicCameraEntity>(GraphicCameraEntity(wpCE.lock(), width, height)); }
		else { return std::make_shared<GraphicCameraEntity>(GraphicCameraEntity()); }
	}

	static std::hash_map<std::string, std::shared_ptr<GraphicObjectEntity>> ObjectEntities;

	void UpdateObjectEntities()
	{
		std::hash_map<std::string, std::weak_ptr<ObjectEntity>> newestObjectList = ObjectEntities::GetAll(); // Get the latest list
		
		std::hash_map<std::string, std::shared_ptr<GraphicObjectEntity>> currentList = ObjectEntities; // Make a copy of our current list

		for(const auto& objectIter : newestObjectList) // go through the latest list
		{
			if(auto obj = objectIter.second.lock())
			{
				auto iter = currentList.find(objectIter.first);
				if(iter != currentList.end()) // if we already have this object
				{
					if(obj->GetTracker() != iter->second->GetTracker()) // check if it has been changed
					{
						iter->second->Update(obj);
					}
					currentList.erase(iter); // erease it as we don't need it anymore
				}
				else // We don't have this one, so add it
				{
					ObjectEntities[obj->GetID()] = std::make_shared<GraphicObjectEntity>(obj);
				}
			}
		}
		
		for(const auto& objectIter : currentList)
		{ // currentList now only has items that are no longer in the latest list so let go through each one and delete them from our list
			ObjectEntities.erase(objectIter.first);
		}
	}

	const std::hash_map<std::string, std::shared_ptr<GraphicObjectEntity>>& GetAllObjectEntities()
	{
		UpdateObjectEntities();
		return ObjectEntities;
	}

	void ClearScreen(std::shared_ptr<GraphicCameraEntity> Camera)
	{
		GraphicManager& graphic = GraphicManager::GetInstance();
		auto& d3dStuff = graphic.D3DStuff;

		// Clear the back buffer 
		auto c = Camera->GetClearColor();
		d3dStuff.pImmediateContext->ClearRenderTargetView(d3dStuff.pRenderTargetView, c.data());
		d3dStuff.pImmediateContext->ClearDepthStencilView(d3dStuff.pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

		ID3D11RenderTargetView* pTempRenderTargetView = d3dStuff.pRenderTargetView;
		ID3D11DepthStencilView* pTempDepthStencilView = d3dStuff.pDepthStencilView;
		d3dStuff.pImmediateContext->OMSetRenderTargets(1, &pTempRenderTargetView, pTempDepthStencilView);
		d3dStuff.pImmediateContext->RSSetViewports(1, &d3dStuff.vp);

	}
	void DrawObjects(std::shared_ptr<GraphicCameraEntity> camera, const std::hash_map<std::string, std::shared_ptr<GraphicObjectEntity>>& list)
	{
		auto& d3dStuff = GraphicManager::GetInstance().D3DStuff;
		ID3D11DeviceContext* pImmediateContext = d3dStuff.pImmediateContext;

		std::vector<std::shared_ptr<GraphicObjectEntity>> objects = camera->FilterInclusionList(list);
		for(const std::shared_ptr<GraphicObjectEntity> object : objects)
		{
			Draw::Setup(camera, object);
		}
	}
};