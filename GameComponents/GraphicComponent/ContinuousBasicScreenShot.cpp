#include "ContinuousBasicScreenShot.h"
#include <GenerateGUID.h>
#include "GraphicManager.h"
#include "BasicTexture.h"

ContinuousBasicScreenShot::ContinuousBasicScreenShot(const std::string& inputID)
	:ContinuousScreenShot(inputID)
{
	this->current = 0;
}
void ContinuousBasicScreenShot::Init()
{
	this->ScreenShot[0] = BasicScreenCapture::Spawn(CHL::GenerateGUID(), this->width, this->height);
	this->ScreenShot[1] = BasicScreenCapture::Spawn(CHL::GenerateGUID(), this->width, this->height);
}
void ContinuousBasicScreenShot::Destory()
{
	this->ScreenShot[0]->Destory();
	this->ScreenShot[1]->Destory();
}
void ContinuousBasicScreenShot::Update(double realTime, double deltaTime)
{

}
void ContinuousBasicScreenShot::Snap(std::hash_map<std::string, SP_INFO>& objects)
{
	this->current += 1;
	if(this->current >= 2){ this->current = 0; }

	this->ScreenShot[this->current]->D3DInfo.cameraMatrix = this->cameraMatrix;
	this->ScreenShot[this->current]->D3DInfo.prespectiveMatrix = this->prespectiveMatrix;
	this->ScreenShot[this->current]->Snap(objects);

	auto allTexture = GraphicManager::GetInstance().AllTexture();
	auto textureIter = allTexture.find(this->TextureID);
	if(textureIter != allTexture.end())
	{
		auto basicTexture = std::dynamic_pointer_cast<BasicTexture>(textureIter->second);
		if(basicTexture != 0)
		{
			basicTexture->D3DInfo.pTexture = this->ScreenShot[this->current]->pScreenTexture;
		}
	}
}
std::shared_ptr<ContinuousScreenShot> ContinuousBasicScreenShot::clone() const
{
	std::shared_ptr<ContinuousScreenShot> newObject(new ContinuousBasicScreenShot(*this));
	newObject->Init();
	return newObject;

}

std::shared_ptr<ContinuousBasicScreenShot> ContinuousBasicScreenShot::Spawn(const std::string& inputID,
																		const std::string& textureID,
																		unsigned int width,
																		unsigned int height,
																		CHL::Matrix4x4 cameraMatrix,
																		CHL::Matrix4x4 prespectiveMatrix)
{
	std::shared_ptr<ContinuousBasicScreenShot> newObject(new ContinuousBasicScreenShot(inputID));

	newObject->TextureID = textureID;
	newObject->width = width;
	newObject->height = height;
	newObject->prespectiveMatrix = prespectiveMatrix;
	newObject->cameraMatrix = cameraMatrix;

	newObject->Init();

	return newObject;
}