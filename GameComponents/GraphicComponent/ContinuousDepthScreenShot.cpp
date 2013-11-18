#include "ContinuousDepthScreenShot.h"
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.
#include <Converter.h>
#include "GraphicManager.h"
#include "BasicTexture.h"

ContinuousDepthScreenShot::ContinuousDepthScreenShot(const std::string& inputID)
:ContinuousScreenShot(inputID)
{
}
void ContinuousDepthScreenShot::Init()
{
	this->ScreenShot = DepthScreenCapture::Spawn(CHL::ToString(boost::uuids::random_generator()()), this->width, this->height);
}
void ContinuousDepthScreenShot::Destory()
{
	this->ScreenShot->Destory();
}
void ContinuousDepthScreenShot::Update(double realTime, double deltaTime)
{

}
void ContinuousDepthScreenShot::Snap(std::hash_map<std::string, SP_INFO>& objects)
{
	this->ScreenShot->D3DInfo.cameraMatrix = this->cameraMatrix;
	this->ScreenShot->D3DInfo.prespectiveMatrix = this->prespectiveMatrix;
	this->ScreenShot->Snap(objects);

	auto allTexture = GraphicManager::GetInstance().AllTexture();
	auto textureIter = allTexture.find(this->TextureID);
	if(textureIter != allTexture.end())
	{
		auto basicTexture = std::dynamic_pointer_cast<BasicTexture>(textureIter->second);
		if(basicTexture != 0)
		{
			basicTexture->D3DInfo.pTexture = this->ScreenShot->pScreenTexture;
		}
	}
}
std::shared_ptr<ContinuousScreenShot> ContinuousDepthScreenShot::clone() const
{
	std::shared_ptr<ContinuousScreenShot> newObject(new ContinuousDepthScreenShot(*this));
	newObject->Init();
	return newObject;

}

std::shared_ptr<ContinuousDepthScreenShot> ContinuousDepthScreenShot::Spawn(const std::string& inputID,
																			const std::string& textureID,
																			unsigned int width,
																			unsigned int height,
																			CHL::Matrix4x4 cameraMatrix,
																			CHL::Matrix4x4 prespectiveMatrix)
{
	std::shared_ptr<ContinuousDepthScreenShot> newObject(new ContinuousDepthScreenShot(inputID));

	newObject->TextureID = textureID;
	newObject->width = width;
	newObject->height = height;
	newObject->prespectiveMatrix = prespectiveMatrix;
	newObject->cameraMatrix = cameraMatrix;

	newObject->Init();

	return newObject;
}