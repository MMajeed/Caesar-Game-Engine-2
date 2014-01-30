#include "Scene.h"
#include <EntityCommunicator\ImportantIDConfig.h>
#include "3DMath.h"
#include "GraphicManager.h"
#include "Buffers.h"
#include "XNAConverter.h"
#include "Process2D.h"
#include "WithinRange.h"

namespace Scene
{
	void SetupSceneCameraInfo(const std::shared_ptr<CameraINFO>& camera, unsigned int width, unsigned int height, SceneInfo& si)
	{
		// Camera
		CML::Vec4 vEye{0.0, 0.0, 0.0, 0.0};
		CML::Vec4 vTM{0.0, 0.0, 1.0, 0.0};
		CML::Vec4 vUp{0.0, 1.0, 0.0, 0.0};
		double pitch = 0.0;
		double yaw = 0.0;
		double roll = 0.0;
		double FovAngleY = 0.785398163;
		double nearZ = 0.01;
		double farZ = 5000.0;
		if(camera)
		{
			vEye = camera->Eye;
			vTM = camera->TargetMagnitude;
			vUp = camera->Up;
			pitch = camera->Pitch;
			yaw = camera->Yaw;
			roll = camera->Roll;
			FovAngleY = camera->FovAngleY;
			nearZ = camera->NearZ;
			farZ = camera->FarZ;
		}

		si.CamerMatrix = ViewCalculation(vEye, vTM, vUp, pitch, yaw, roll);
		si.Eye = vEye;
		if(FovAngleY > 0.0)
			si.ProjectionMatrix = PerspectiveFovLHCalculation(FovAngleY, (double)width / (double)height, nearZ, farZ);
		else
			si.ProjectionMatrix = OrthographicLHCalculation(width, height, nearZ, farZ);

		si.TwoDimMatrix = OrthographicLHCalculation(width, height, nearZ, farZ);
		si.width = width;
		si.height = height;
		si.farZ = farZ;
		si.nearZ = nearZ;
	}
	void SetupSceneExtraInfo(const std::shared_ptr<CameraINFO>& camera, unsigned int width, unsigned int height, SceneInfo& si)
	{
		CML::Vec4 clearColor{0.5, 0.5, 0.5, 1.0};
		bool process2D = true;
		std::vector<std::string> global2DTexture;
		std::vector<std::string> globalCubeTexture;
		std::array<float, 16> globalUserData;
		std::fill(globalUserData.begin(), globalUserData.end(), 0.0f);
		SceneInfo::InclusionType inclusionState = SceneInfo::InclusionType::Exclude;
		std::set<std::string> objList;
		if(camera)
		{
			clearColor = camera->ClearColor;
			process2D = camera->Process2D;
			global2DTexture = camera->Global2DTexture;
			globalCubeTexture = camera->GlobalCubeTexture;
			globalUserData = camera->GlobalUserData;
			inclusionState = static_cast<SceneInfo::InclusionType>(camera->InclusionState);
			objList = camera->ObjectList;
		}

		si.width = width;
		si.height = height;
		si.ClearColour = clearColor;
		si.process2D = process2D;
		si.Global2DTexture = global2DTexture;
		si.GlobalCubeTexture = globalCubeTexture;
		si.GlobalUserData = globalUserData;
		si.InclusionState = inclusionState;
		si.ObjectList = objList;
	}
	SceneInfo SetupScene(const std::shared_ptr<CameraINFO>& camera, unsigned int width, unsigned int height)
	{
		SceneInfo returnValue;

		Scene::SetupSceneCameraInfo(camera, width, height, returnValue);
		Scene::SetupSceneExtraInfo(camera, width, height, returnValue);

		return returnValue;
	}
	void SetupConstantBuffer(const SceneInfo& si)
	{
		GraphicManager& graphic = GraphicManager::GetInstance();
		auto& d3dStuff = graphic.D3DStuff;

		cBuffer::cbInfo cbInfo;

		XMFLOAT4X4 view4x4 = Convert4x4(si.CamerMatrix);;
		XMFLOAT4X4 proj4x4 = Convert4x4(si.ProjectionMatrix);;

		cbInfo.view = XMMatrixTranspose(XMLoadFloat4x4(&view4x4));
		cbInfo.proj = XMMatrixTranspose(XMLoadFloat4x4(&proj4x4));
		cbInfo.eye = ConvertVec4(si.Eye);
		cbInfo.numberOfGlobal2DTexture = si.Global2DTexture.size() < cBuffer::numOfTextures ? si.Global2DTexture.size() : cBuffer::numOfTextures;
		
		for(unsigned int i = 0; i < 4; ++i)
		{
			int row = i * 4;
			cbInfo.globalUserData(i, 0) = si.GlobalUserData[row + 0];
			cbInfo.globalUserData(i, 1) = si.GlobalUserData[row + 1];
			cbInfo.globalUserData(i, 2) = si.GlobalUserData[row + 2];
			cbInfo.globalUserData(i, 3) = si.GlobalUserData[row + 3];
		}

		d3dStuff.pImmediateContext->UpdateSubresource(d3dStuff.pCBInfo, 0, NULL, &cbInfo, 0, 0);
	}
	void SetupGlobalTexture(const SceneInfo& si)
	{
		GraphicManager& graphic = GraphicManager::GetInstance();
		if(si.Global2DTexture.size() > 0)
		{
			ID3D11ShaderResourceView* pTexture[cBuffer::numOfTextures] = {0};
			std::size_t limit = si.Global2DTexture.size() < cBuffer::numOfTextures ? si.Global2DTexture.size() : cBuffer::numOfTextures;
			for(std::size_t i = 0; i < limit; ++i)
			{
				std::string textureID = si.Global2DTexture[i];
				auto textureIter = graphic.textures.find(textureID);
				if(textureIter != graphic.textures.end())
				{
					pTexture[i] = textureIter->second->D3DInfo.pTexture;
				}
			}
			graphic.D3DStuff.pImmediateContext->VSSetShaderResources(0, limit, pTexture);
			graphic.D3DStuff.pImmediateContext->GSSetShaderResources(0, limit, pTexture);
			graphic.D3DStuff.pImmediateContext->PSSetShaderResources(0, limit, pTexture);
		}

		if(si.GlobalCubeTexture.size() > 0)
		{
			ID3D11ShaderResourceView* pTexture[cBuffer::numOfTextures] = {0};
			std::size_t limit = si.GlobalCubeTexture.size() < cBuffer::numOfTextures ? si.GlobalCubeTexture.size() : cBuffer::numOfTextures;
			for(std::size_t i = 0; i < limit; ++i)
			{
				std::string textureID = si.GlobalCubeTexture[i];
				auto textureIter = graphic.textures.find(textureID);
				if(textureIter != graphic.textures.end())
				{
					pTexture[i] = textureIter->second->D3DInfo.pTexture;
				}
			}
			graphic.D3DStuff.pImmediateContext->VSSetShaderResources(5, limit, pTexture);
			graphic.D3DStuff.pImmediateContext->GSSetShaderResources(5, limit, pTexture);
			graphic.D3DStuff.pImmediateContext->PSSetShaderResources(5, limit, pTexture);
		}
	}
	void ClearScreen(const SceneInfo& si)
	{
		GraphicManager& graphic = GraphicManager::GetInstance();
		auto& d3dStuff = graphic.D3DStuff;

		// Clear the back buffer 
		float ClearColor[4] = {(float)si.ClearColour(0), (float)si.ClearColour(1), (float)si.ClearColour(2), 1.0f}; // red,green,blue,alpha
		d3dStuff.pImmediateContext->ClearRenderTargetView(d3dStuff.pRenderTargetView, ClearColor);
		d3dStuff.pImmediateContext->ClearDepthStencilView(d3dStuff.pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	}
	std::vector<DrawableObject> FilterScene(const std::hash_map<std::string, SP_INFO>& objects, const SceneInfo& si)
	{
		GraphicManager& graphic = GraphicManager::GetInstance();

		std::vector<DrawableObject> vecObjects;
		vecObjects.reserve(objects.size());

		
		for(auto iterObj = objects.begin();
			iterObj != objects.end();
			++iterObj)
		{
			if(si.InclusionState == SceneInfo::InclusionType::Exclude)
			{
				auto iterSceneObj = si.ObjectList.find(iterObj->first);
				if(iterSceneObj != si.ObjectList.end()){ continue; } // It is on the list, so exclude it
			}
			else if(si.InclusionState == SceneInfo::InclusionType::Include)
			{
				auto iterSceneObj = si.ObjectList.find(iterObj->first);
				if(iterSceneObj == si.ObjectList.end()){ continue; } // It is not on the list, so don't include it
			}

			std::shared_ptr<ObjectINFO> objInfo = std::dynamic_pointer_cast<ObjectINFO>(iterObj->second);
			if(!objInfo){ continue; }

			auto drawableIter = graphic.objectDrawables.find(objInfo->DrawObjID);
			if(drawableIter == graphic.objectDrawables.end()){ continue; }// If it didn't fine then continue


			if(si.process2D == false)
			{
				if(Process2D::Filter(si, {objInfo, drawableIter->second})){ continue; }
			}
			if(!WithinRange::Filter(si, {objInfo, drawableIter->second})){ continue; }

			vecObjects.push_back({objInfo, drawableIter->second});
		}

		const CML::Vec4& eye = si.Eye;
		std::sort(vecObjects.begin(), vecObjects.end(),
				  [eye](const DrawableObject& a, const DrawableObject& b) -> bool
		{
			float rankA = 0.0f; float rankB = 0.0f;

			if(a.ObjInfo->Diffuse[3] >= 1.0)	 { rankA += 100000.0f; }
			else if(a.ObjInfo->Diffuse[3] < 1.0) { rankA += Length(eye, a.ObjInfo->Location); }

			if(b.ObjInfo->Diffuse[3] >= 1.0)	 { rankB += 100000.0f; }
			else if(b.ObjInfo->Diffuse[3] < 1.0) { rankB += Length(eye, b.ObjInfo->Location); }

			if(a.ObjInfo->Depth == false) { rankA -= 1000000.0f; }
			if(b.ObjInfo->Depth == false) { rankB -= 1000000.0f; }

			return rankA > rankB;
		});


		return vecObjects;
	}
	void DrawObjects(const std::vector<DrawableObject>& objects, const SceneInfo& si)
	{
		for(auto iterObj = objects.begin();
			iterObj != objects.end();
			++iterObj)
		{
			iterObj->Drawable->Draw(iterObj->ObjInfo, si);
		}
	}
};