#include "CBHardVariables.h"

#include "XNAConverter.h"
#include "3DMath.h"
#include <Windows.h>
#include <xnamath.h>
#include <Logger.h>

CBHardVariables::CBHardVariables(std::vector<char>& bytes, const unsigned int StartOffset, const unsigned int sizeOfValue)
	: CBufferVariables(bytes, StartOffset), sizeOfValue(sizeOfValue)
{
	const unsigned int end = this->sizeOfValue + StartOffset;

	if(end != this->sizeOfValue) // Check that the size isn't the same
	{
		Logger::LogError("Failed at creating dynamic constant buffer as wrong data type is used for " + this->VName());
	}
	else if(end < bytes.size()) // check that we are not over writting
	{
		Logger::LogError("Failed at creating dynamic constant buffer as size of the buffer was not large enoughfor " + this->VName());
	}
}

//---------------------------------------------------------------------

CBufferWorld::CBufferWorld(std::vector<char>& bytes, const unsigned int StartOffset) : CBHardVariables(bytes, StartOffset, sizeof(XMMATRIX))
{
}
void CBufferWorld::Update(std::shared_ptr<ObjectEntity> object, const SceneInfo& si)
{
	static const unsigned int sizeOfValue = this->sizeOfValue;
	const unsigned int copyStartingAt = this->StartOffset;
	
	CML::Matrix4x4 valueCML;// = object->GetTranslationMatrix();
	XMFLOAT4X4 valueXM = Convert4x4(valueCML);
	XMMATRIX value = XMLoadFloat4x4(&valueXM);

	value = XMMatrixTranspose(value);
	memcpy(&bytes[copyStartingAt], &value, sizeOfValue);
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
void CBufferView::Update(std::shared_ptr<ObjectEntity> object, const SceneInfo& si)
{
	static const unsigned int sizeOfValue = this->sizeOfValue;
	const unsigned int copyStartingAt = this->StartOffset;

	CML::Matrix4x4 valueCML = si.CamerMatrix;
	XMFLOAT4X4 valueXM = Convert4x4(valueCML);
	XMMATRIX value = XMLoadFloat4x4(&valueXM);

	value = XMMatrixTranspose(value);
	memcpy(&bytes[copyStartingAt], &value, sizeOfValue);
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
void CBufferProjection::Update(std::shared_ptr<ObjectEntity> object, const SceneInfo& si)
{
	static const unsigned int sizeOfValue = this->sizeOfValue;
	const unsigned int copyStartingAt = this->StartOffset;

	CML::Matrix4x4 valueCML = si.ProjectionMatrix;
	XMFLOAT4X4 valueXM = Convert4x4(valueCML);
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
void CBufferWVP::Update(std::shared_ptr<ObjectEntity> object, const SceneInfo& si)
{
	static const unsigned int sizeOfValue = this->sizeOfValue;
	const unsigned int copyStartingAt = this->StartOffset;

	auto h = ObjectCalculation(object->GetLocation(), object->GetRotation(), object->GetScale());

	XMFLOAT4X4 worldMatrix = Convert4x4(h);
	XMFLOAT4X4 prespectiveMatrix = Convert4x4(si.ProjectionMatrix);
	XMFLOAT4X4 viewMatrix = Convert4x4(si.CamerMatrix);

	XMMATRIX value = XMLoadFloat4x4(&worldMatrix) * XMLoadFloat4x4(&viewMatrix) * XMLoadFloat4x4(&prespectiveMatrix);

	value = XMMatrixTranspose(value);
	memcpy(&bytes[copyStartingAt], &value, sizeOfValue);
}
std::shared_ptr<CBHardVariables> CBufferWVP::Spawn(std::vector<char>& bytes, const unsigned int StartOffset)
{
	std::shared_ptr<CBHardVariables> returnValue(new CBufferWVP(bytes, StartOffset));
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

	return returnValue;
}

std::hash_map<const std::string, VariableCreatorFunction> VariableTypes = PopulateVariableTypes();