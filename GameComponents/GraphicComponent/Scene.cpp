#include "Scene.h"
#include <EntityCommunicator\ImportantIDConfig.h>
#include <3DMath.h>
#include "GraphicManager.h"
#include "Buffers.h"
#include <XNAConverter.h>

namespace Scene
{
	SceneInfo SetupScene(const std::shared_ptr<CameraINFO>& camera, unsigned int width, unsigned int height)
	{
		// Camera
		CHL::Vec4 vEye{0.0, 0.0, 0.0, 0.0};
		CHL::Vec4 vTM{0.0, 0.0, 1.0, 0.0};
		CHL::Vec4 vUp{0.0, 1.0, 0.0, 0.0};
		double pitch = 0.0;	
		double yaw = 0.0;	
		double roll = 0.0;
		double FovAngleY = 0.785398163;
		double nearZ = 0.01;
		double farZ = 5000.0;
		CHL::Vec4 clearColor{0.5, 0.5, 0.5, 1.0};

		if(camera)
		{
			vEye = camera->Eye;
			vTM = camera->TargetMagnitude;
			vUp = camera->Up;
			pitch = camera->Pitch;
			yaw = camera->Yaw;
			roll = camera->Roll;
			FovAngleY = camera->FovAngleY;
			nearZ = camera->nearZ;
			farZ = camera->farZ;
			clearColor = camera->ClearColor;
		}

		SceneInfo returnValue;
		returnValue.CamerMatrix = CHL::ViewCalculation(vEye, vTM, vUp, pitch, yaw, roll);
		returnValue.Eye = vEye;
		if(FovAngleY > 0.0)
			returnValue.ProjectionMatrix = CHL::PerspectiveFovLHCalculation(FovAngleY, (double)width / (double)height, nearZ, farZ);
		else
			returnValue.ProjectionMatrix = CHL::OrthographicLHCalculation(width, height, nearZ, farZ);

		returnValue.TwoDimMatrix = CHL::OrthographicLHCalculation(width, height, nearZ, farZ);
		returnValue.width = width;
		returnValue.height = height;
		returnValue.ClearColour = clearColor;
		returnValue.farZ = farZ;
		returnValue.nearZ = nearZ;
		return returnValue;
	}
	void SetupConstantBuffer(const SceneInfo& si)
	{
		GraphicManager& graphic = GraphicManager::GetInstance();
		auto& d3dStuff = graphic.D3DStuff;

		cBuffer::cbInfo cbInfo;

		XMFLOAT4X4 view4x4 = CHL::Convert4x4(si.CamerMatrix);;
		XMFLOAT4X4 proj4x4 = CHL::Convert4x4(si.ProjectionMatrix);;

		cbInfo.view = XMMatrixTranspose(XMLoadFloat4x4(&view4x4));
		cbInfo.proj = XMMatrixTranspose(XMLoadFloat4x4(&proj4x4));
		cbInfo.eye = CHL::ConvertVec4(si.Eye);
		
		d3dStuff.pImmediateContext->UpdateSubresource(d3dStuff.pCBInfo, 0, NULL, &cbInfo, 0, 0);
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
	std::vector<std::shared_ptr<ObjectINFO>> FilterScene(const std::hash_map<std::string, SP_INFO>& objects, const SceneInfo& si)
	{
		std::vector<std::shared_ptr<ObjectINFO>> vecSpecialObjects; // For transparency and depth
		std::vector<std::shared_ptr<ObjectINFO>> vecRegularObjects;
		vecSpecialObjects.reserve(objects.size());
		vecRegularObjects.reserve(objects.size());

		for(auto iterObj = objects.begin();
			iterObj != objects.end();
			++iterObj)
		{
			std::shared_ptr<ObjectINFO> objInfo = std::dynamic_pointer_cast<ObjectINFO>(iterObj->second);
			if(!objInfo){ continue; }

			if(objInfo->Diffuse[3] != 1.0f || objInfo->Depth == false)
			{
				vecSpecialObjects.push_back(objInfo);
			}
			else
			{
				vecRegularObjects.push_back(objInfo);
			}
		}

		const CHL::Vec4& eye = si.Eye;
		std::sort(vecSpecialObjects.begin(), vecSpecialObjects.end(),
				  [eye](const std::shared_ptr<ObjectINFO>& a, const std::shared_ptr<ObjectINFO>& b) -> bool
		{
			float rankA = 0.0f; float rankB = 0.0f;

			rankA += CHL::Length(eye, a->Location);
			rankB += CHL::Length(eye, b->Location);

			if(a->Depth == false) { rankA -= 1000000.0f; }
			if(b->Depth == false) { rankB -= 1000000.0f; }

			return rankA > rankB;
		});


		std::vector<std::shared_ptr<ObjectINFO>> returnValue;
		returnValue.reserve(vecSpecialObjects.size() + vecRegularObjects.size()); // preallocate memory
		returnValue.insert(returnValue.end(), vecRegularObjects.begin(), vecRegularObjects.end());
		returnValue.insert(returnValue.end(), vecSpecialObjects.begin(), vecSpecialObjects.end());
		return returnValue;
	}
	void DrawObjects(const std::vector<std::shared_ptr<ObjectINFO>>& objects, const SceneInfo& si)
	{
		GraphicManager& graphic = GraphicManager::GetInstance();

		for(auto iterObj = objects.begin();
			iterObj != objects.end();
			++iterObj)
		{

			auto drawableIter = graphic.objectDrawables.find((*iterObj)->DrawObjID);
			if(drawableIter == graphic.objectDrawables.end()){ continue; }// If it didn't fine then continue

			drawableIter->second->Draw(*iterObj, si);

		}
	}
};