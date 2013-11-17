#include "ContinuousCubeScreenShot.h"
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.
#include <Converter.h>
#include "GraphicManager.h"
#include "BasicTexture.h"

ContinuousCubeScreenShot::ContinuousCubeScreenShot(const std::string& inputID)
:ContinuousScreenShot(inputID)
{
	this->current = 0;
}
void ContinuousCubeScreenShot::Init()
{
	this->ScreenShot[0] = CubeScreenCapture::Spawn(CHL::ToString(boost::uuids::random_generator()()), this->width, this->height);
	this->ScreenShot[1] = CubeScreenCapture::Spawn(CHL::ToString(boost::uuids::random_generator()()), this->width, this->height);
}
void ContinuousCubeScreenShot::Destory()
{
	this->ScreenShot[0]->Destory();
	this->ScreenShot[1]->Destory();
}
void ContinuousCubeScreenShot::Update(double realTime, double deltaTime)
{

}
void ContinuousCubeScreenShot::Snap(TypedefObject::ObjectVector& objects)
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
std::shared_ptr<ContinuousScreenShot> ContinuousCubeScreenShot::clone() const
{
	std::shared_ptr<ContinuousScreenShot> newObject(new ContinuousCubeScreenShot(*this));
	newObject->Init();
	return newObject;

}

std::shared_ptr<ContinuousCubeScreenShot> ContinuousCubeScreenShot::Spawn(	const std::string& inputID,
																			const std::string& textureID,
																			unsigned int width,
																			unsigned int height,
																			CHL::Vec4 eye)
{
	std::shared_ptr<ContinuousCubeScreenShot> newObject(new ContinuousCubeScreenShot(inputID));

	newObject->TextureID = textureID;
	newObject->width = width;
	newObject->height = height;
	newObject->eye = eye;

	newObject->Init();

	return newObject;
}