#include "CBHardVariables.h"

#include "XNAConverter.h"
#include "3DMath.h"
#include <Windows.h>
#include <xnamath.h>
#include <Logger.h>
#include <ByteCopy.h>

CBHardVariables::CBHardVariables(std::vector<char>& bytes, const unsigned int StartOffset, const unsigned int sizeOfValue)
	: CBVariables(bytes, StartOffset), sizeOfValue(sizeOfValue)
{
	const unsigned int end = this->sizeOfValue + StartOffset;

	if(end > bytes.size()) // check that we are not over writting
	{
		Logger::LogError("Failed at creating dynamic constant buffer as size of the buffer was not large enough for " + this->VName());
	}
}

//---------------------------------------------------------------------

CBufferWorld::CBufferWorld(std::vector<char>& bytes, const unsigned int StartOffset) : CBHardVariables(bytes, StartOffset, sizeof(XMMATRIX))
{
}
void CBufferWorld::Update(const GraphicCameraEntity& camera, const GraphicObjectEntity& object)
{
	static const unsigned int sizeOfValue = this->sizeOfValue;
	const unsigned int copyStartingAt = this->StartOffset;
	
	XMFLOAT4X4 valueXM = object.GetWorldTransformation();
	XMMATRIX value = XMLoadFloat4x4(&valueXM);

	value = XMMatrixTranspose(value);

	CHL::ByteCopy<XMMATRIX>(value, bytes, copyStartingAt);
}
std::shared_ptr<CBHardVariables> CBufferWorld::Spawn(std::vector<char>& bytes, const unsigned int StartOffset)
{
	std::shared_ptr<CBHardVariables> returnValue(new CBufferWorld(bytes, StartOffset));
	return returnValue;
}

//---------------------------------------------------------------------

CBufferView::CBufferView(std::vector<char>& bytes, const unsigned int StartOffset)
: CBHardVariables(bytes, StartOffset, sizeof(XMMATRIX))
{
}
void CBufferView::Update(const GraphicCameraEntity& camera, const GraphicObjectEntity& object)
{
	static const unsigned int sizeOfValue = this->sizeOfValue;
	const unsigned int copyStartingAt = this->StartOffset;

	XMFLOAT4X4 valueXM = camera.GetView();
	XMMATRIX value = XMLoadFloat4x4(&valueXM);

	value = XMMatrixTranspose(value);
	CHL::ByteCopy<XMMATRIX>(value, bytes, copyStartingAt);
}
std::shared_ptr<CBHardVariables> CBufferView::Spawn(std::vector<char>& bytes, const unsigned int StartOffset)
{
	std::shared_ptr<CBHardVariables> returnValue(new CBufferView(bytes, StartOffset));
	return returnValue;
}

//---------------------------------------------------------------------

CBufferProjection::CBufferProjection(std::vector<char>& bytes, const unsigned int StartOffset)
: CBHardVariables(bytes, StartOffset, sizeof(XMMATRIX))
{
}
void CBufferProjection::Update(const GraphicCameraEntity& camera, const GraphicObjectEntity& object)
{
	static const unsigned int sizeOfValue = this->sizeOfValue;
	const unsigned int copyStartingAt = this->StartOffset;

	XMFLOAT4X4 valueXM = camera.GetProjection();
	XMMATRIX value = XMLoadFloat4x4(&valueXM);

	value = XMMatrixTranspose(value);
	memcpy(&bytes[copyStartingAt], &value, sizeOfValue);
}
std::shared_ptr<CBHardVariables> CBufferProjection::Spawn(std::vector<char>& bytes, const unsigned int StartOffset)
{
	std::shared_ptr<CBHardVariables> returnValue(new CBufferProjection(bytes, StartOffset));
	return returnValue;
}

//---------------------------------------------------------------------

CBufferWVP::CBufferWVP(std::vector<char>& bytes, const unsigned int StartOffset)
: CBHardVariables(bytes, StartOffset, sizeof(XMMATRIX))
{
}
void CBufferWVP::Update(const GraphicCameraEntity& camera, const GraphicObjectEntity& object)
{
	static const unsigned int sizeOfValue = this->sizeOfValue;
	const unsigned int copyStartingAt = this->StartOffset;

	XMFLOAT4X4 worldMatrix = object.GetWorldTransformation();
	XMFLOAT4X4 prespectiveMatrix = camera.GetProjection();
	XMFLOAT4X4 viewMatrix = camera.GetView();

	XMMATRIX value = XMLoadFloat4x4(&worldMatrix) * XMLoadFloat4x4(&viewMatrix) * XMLoadFloat4x4(&prespectiveMatrix);

	value = XMMatrixTranspose(value);
	CHL::ByteCopy<XMMATRIX>(value, bytes, copyStartingAt);
}
std::shared_ptr<CBHardVariables> CBufferWVP::Spawn(std::vector<char>& bytes, const unsigned int StartOffset)
{
	std::shared_ptr<CBHardVariables> returnValue(new CBufferWVP(bytes, StartOffset));
	return returnValue;
}

//---------------------------------------------------------------------

CBufferEye::CBufferEye(std::vector<char>& bytes, const unsigned int StartOffset)
: CBHardVariables(bytes, StartOffset, sizeof(XMFLOAT4))
{
}
void CBufferEye::Update(const GraphicCameraEntity& camera, const GraphicObjectEntity& object)
{
	static const unsigned int sizeOfValue = this->sizeOfValue;
	const unsigned int copyStartingAt = this->StartOffset;

	XMFLOAT4 value = camera.GetEye();

	CHL::ByteCopy<XMFLOAT4>(value, bytes, copyStartingAt);
}
std::shared_ptr<CBHardVariables> CBufferEye::Spawn(std::vector<char>& bytes, const unsigned int StartOffset)
{
	std::shared_ptr<CBHardVariables> returnValue(new CBufferEye(bytes, StartOffset));
	return returnValue;
}

//---------------------------------------------------------------------

std::hash_map<const std::string, VariableCreatorFunction> PopulateVariableTypes()
{
	std::hash_map<const std::string, VariableCreatorFunction> returnValue;

	returnValue[CBufferWorld::Name()] = CBufferWorld::Spawn;
	returnValue[CBufferView::Name()] = CBufferView::Spawn;
	returnValue[CBufferProjection::Name()] = CBufferProjection::Spawn;
	returnValue[CBufferWVP::Name()] = CBufferWVP::Spawn;
	returnValue[CBufferEye::Name()] = CBufferEye::Spawn;

	return returnValue;
}

std::hash_map<const std::string, VariableCreatorFunction> VariableTypes = PopulateVariableTypes();

VariableCreatorFunction FindCBHardVariable(std::string Name)
{
	VariableCreatorFunction returnValue;
		
	auto iter = VariableTypes.find(Name);
	if(iter != VariableTypes.end())
	{
		returnValue = iter->second;
	}

	return returnValue;
}