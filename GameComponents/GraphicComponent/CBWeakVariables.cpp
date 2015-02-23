#include "CBWeakVariables.h"

#include "XNAConverter.h"
#include <Windows.h>
#include <xnamath.h>
#include <Logger.h>
#include <ByteCopy.h>

CBWeakVariables::CBWeakVariables(std::vector<char>& bytes,
											 const unsigned int StartOffset,
											 const unsigned int sizeOfValue,
											 const std::string Name)
: CBVariables(bytes, StartOffset), sizeOfValue(sizeOfValue), Name(Name)
{
	const unsigned int end = this->sizeOfValue + StartOffset;

	if(end > bytes.size()) // check that we are not over writting
	{
		Logger::LogError("Failed at creating dynamic constant buffer as size of the buffer was not large enough for " + this->Name);
	}
}
void CBWeakVariables::Update(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicDrawSettingsEntity> drawSettings, std::shared_ptr<GraphicObjectEntity> object)
{
	std::vector<char> dataToCopy(this->sizeOfValue);

	std::shared_ptr<Object> objectUserData = object->findUserData(this->Name);
	if(objectUserData == false)
	{// If we didn't find it in object, check camera
		objectUserData = drawSettings->findUserData(this->Name);
	}


	if(std::shared_ptr<GenericObj<float>> value = GenericObj<float>::Cast(objectUserData))
	{
		float tempV = *value;
		CHL::ByteCopy(tempV, dataToCopy);
	}
	else if(std::shared_ptr<GenericObj<CML::Vec4>> value = GenericObj<CML::Vec4>::Cast(objectUserData))
	{
		XMFLOAT4 tempV = ConvertVec4(*value);
		CHL::ByteCopy(tempV, dataToCopy);
	}
	else if(std::shared_ptr<GenericObj<CML::Matrix4x4>> value = GenericObj<CML::Matrix4x4>::Cast(objectUserData))
	{
		XMFLOAT4X4 xm4x4Value = Convert4x4(*value);
		XMMATRIX tempV = XMLoadFloat4x4(&xm4x4Value);
		tempV = XMMatrixTranspose(tempV);
		CHL::ByteCopy(tempV, dataToCopy);
	}
	else
	{
		XMMATRIX tempV = XMMatrixIdentity();
		tempV = XMMatrixTranspose(tempV);
		CHL::ByteCopy(tempV, dataToCopy);
	}

	auto beginCopy = dataToCopy.begin();
	auto endCopy = dataToCopy.end();

	if(this->sizeOfValue < dataToCopy.size())
	{ // This data is too big, let us copy only what we can
		endCopy = beginCopy + (this->sizeOfValue - 1);
	}

	auto copyTo = this->bytes.begin() + this->StartOffset;

	std::copy(beginCopy, endCopy, copyTo);
}
std::shared_ptr<CBWeakVariables> CBWeakVariables::Spawn(std::vector<char>& bytes,
																	const unsigned int StartOffset,
																	const unsigned int sizeOfValue,
																	const std::string Name)
{
	std::shared_ptr<CBWeakVariables> returnValue(new CBWeakVariables(bytes, StartOffset, sizeOfValue, Name));
	return returnValue;
}