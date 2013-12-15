#include "CubeScreenCapture.h"
#include <GenerateGUID.h>
#include "GraphicManager.h"
#include "BasicTexture.h"

CubeScreenCapture::CubeScreenCapture(const std::string& inputID)
:ScreenCapture(inputID)
{
	this->current = 0;
}
void CubeScreenCapture::Init()
{
	this->ScreenShot[0] = CubeScreenShot::Spawn(CHL::GenerateGUID(), this->width, this->height);
	this->ScreenShot[1] = CubeScreenShot::Spawn(CHL::GenerateGUID(), this->width, this->height);
}
void CubeScreenCapture::Destory()
{
	this->ScreenShot[0]->Release();
	this->ScreenShot[1]->Release();
}
void CubeScreenCapture::Update(double realTime, double deltaTime)
{

}
void CubeScreenCapture::Snap(std::hash_map<std::string, SP_INFO>& objects)
{
	this->current += 1;
	if(this->current >= 2){ this->current = 0; }

	this->ScreenShot[this->current]->D3DInfo.Eye = this->eye;
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
std::shared_ptr<ScreenCapture> CubeScreenCapture::clone() const
{
	std::shared_ptr<ScreenCapture> newObject(new CubeScreenCapture(*this));
	newObject->Init();
	return newObject;

}

std::shared_ptr<CubeScreenCapture> CubeScreenCapture::Spawn(	const std::string& inputID,
																			const std::string& textureID,
																			unsigned int width,
																			unsigned int height,
																			CHL::Vec4 eye)
{
	std::shared_ptr<CubeScreenCapture> newObject(new CubeScreenCapture(inputID));

	newObject->TextureID = textureID;
	newObject->width = width;
	newObject->height = height;
	newObject->eye = eye;

	newObject->Init();

	return newObject;
}