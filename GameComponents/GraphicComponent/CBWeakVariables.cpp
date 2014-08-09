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
void CBWeakVariables::Update(const GraphicCameraEntity& camera, const GraphicObjectEntity& object)
{
	std::vector<char> dataToCopy(this->sizeOfValue);

	std::shared_ptr<Object> objectUserData = object.FindUserData(this->Name);
	if(objectUserData)
	{
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
	}
	else // If we didn't find it in object, check camera
	{
		/*std::hash_map<std::string, std::vector<char>> cameraUserData = camera.GetUserData();
		auto iter = cameraUserData.find(this->Name);
		if(iter != cameraUserData.end())
		{
			dataToCopy = iter->second;
		}*/
	}

	if(dataToCopy.size() > 0)
	{ // if it found some value
		auto beginCopy = dataToCopy.begin();
		auto endCopy = dataToCopy.end();

		if(this->sizeOfValue < dataToCopy.size())
		{ // This data is too big, let us copy only what we can
			endCopy = beginCopy + (this->sizeOfValue - 1);
		}

		auto copyTo = this->bytes.begin() + this->StartOffset;

		std::copy(beginCopy, endCopy, copyTo);
	}
}
std::shared_ptr<CBWeakVariables> CBWeakVariables::Spawn(std::vector<char>& bytes,
																	const unsigned int StartOffset,
																	const unsigned int sizeOfValue,
																	const std::string Name)
{
	std::shared_ptr<CBWeakVariables> returnValue(new CBWeakVariables(bytes, StartOffset, sizeOfValue, Name));
	return returnValue;
}