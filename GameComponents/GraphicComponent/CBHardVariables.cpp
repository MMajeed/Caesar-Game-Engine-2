#include "CBHardVariables.h"

#include "XNAConverter.h"
#include "GraphicManager.h"
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
void CBufferWorld::Update(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicObjectEntity> object)
{
	static const unsigned int sizeOfValue = this->sizeOfValue;
	const unsigned int copyStartingAt = this->StartOffset;

	if(object)
	{
		XMFLOAT4X4 valueXM = object->GetWorld();
		XMMATRIX value = XMLoadFloat4x4(&valueXM);

		value = XMMatrixTranspose(value);

		CHL::ByteCopy<XMMATRIX>(value, bytes, copyStartingAt);
	}
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
void CBufferView::Update(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicObjectEntity> object)
{
	static const unsigned int sizeOfValue = this->sizeOfValue;
	const unsigned int copyStartingAt = this->StartOffset;

	if(camera)
	{
		XMFLOAT4X4 valueXM = camera->GetView();
		XMMATRIX value = XMLoadFloat4x4(&valueXM);

		value = XMMatrixTranspose(value);
		CHL::ByteCopy<XMMATRIX>(value, bytes, copyStartingAt);
	}
	else
	{
		XMMATRIX value = XMMatrixIdentity();
		value = XMMatrixTranspose(value);
		CHL::ByteCopy<XMMATRIX>(value, bytes, copyStartingAt);
	}
}
std::shared_ptr<CBHardVariables> CBufferView::Spawn(std::vector<char>& bytes, const unsigned int StartOffset)
{
	std::shared_ptr<CBHardVariables> returnValue(new CBufferView(bytes, StartOffset));
	return returnValue;
}

//---------------------------------------------------------------------

CBufferView2D::CBufferView2D(std::vector<char>& bytes, const unsigned int StartOffset)
	: CBHardVariables(bytes, StartOffset, sizeof(XMMATRIX))
{
}
void CBufferView2D::Update(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicObjectEntity> object)
{
	static const unsigned int sizeOfValue = this->sizeOfValue;
	const unsigned int copyStartingAt = this->StartOffset;

	if(object)
	{
		XMFLOAT4X4 valueXM = camera->GetView2D();
		XMMATRIX value = XMLoadFloat4x4(&valueXM);

		value = XMMatrixTranspose(value);
		CHL::ByteCopy<XMMATRIX>(value, bytes, copyStartingAt);
	}
	else
	{
		XMMATRIX value = XMMatrixIdentity();
		value = XMMatrixTranspose(value);
		CHL::ByteCopy<XMMATRIX>(value, bytes, copyStartingAt);
	}
}
std::shared_ptr<CBHardVariables> CBufferView2D::Spawn(std::vector<char>& bytes, const unsigned int StartOffset)
{
	std::shared_ptr<CBHardVariables> returnValue(new CBufferView2D(bytes, StartOffset));
	return returnValue;
}

//---------------------------------------------------------------------

CBufferPerspective::CBufferPerspective(std::vector<char>& bytes, const unsigned int StartOffset)
: CBHardVariables(bytes, StartOffset, sizeof(XMMATRIX))
{
}
void CBufferPerspective::Update(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicObjectEntity> object)
{
	static const unsigned int sizeOfValue = this->sizeOfValue;
	const unsigned int copyStartingAt = this->StartOffset;

	if(camera)
	{
		XMFLOAT4X4 valueXM = camera->GetPerspective();
		XMMATRIX value = XMLoadFloat4x4(&valueXM);

		value = XMMatrixTranspose(value);
		memcpy(&bytes[copyStartingAt], &value, sizeOfValue);
	}
	else
	{
		XMMATRIX value = XMMatrixIdentity();
		value = XMMatrixTranspose(value);
		CHL::ByteCopy<XMMATRIX>(value, bytes, copyStartingAt);
	}
}
std::shared_ptr<CBHardVariables> CBufferPerspective::Spawn(std::vector<char>& bytes, const unsigned int StartOffset)
{
	std::shared_ptr<CBHardVariables> returnValue(new CBufferPerspective(bytes, StartOffset));
	return returnValue;
}

//---------------------------------------------------------------------

CBufferOrthogonal::CBufferOrthogonal(std::vector<char>& bytes, const unsigned int StartOffset)
: CBHardVariables(bytes, StartOffset, sizeof(XMMATRIX))
{
}
void CBufferOrthogonal::Update(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicObjectEntity> object)
{
	static const unsigned int sizeOfValue = this->sizeOfValue;
	const unsigned int copyStartingAt = this->StartOffset;

	if(camera)
	{
		XMFLOAT4X4 valueXM = camera->GetOrthogonal();
		XMMATRIX value = XMLoadFloat4x4(&valueXM);

		value = XMMatrixTranspose(value);
		memcpy(&bytes[copyStartingAt], &value, sizeOfValue);
	}
	else
	{
		XMMATRIX value = XMMatrixIdentity();
		value = XMMatrixTranspose(value);
		CHL::ByteCopy<XMMATRIX>(value, bytes, copyStartingAt);
	}
}
std::shared_ptr<CBHardVariables> CBufferOrthogonal::Spawn(std::vector<char>& bytes, const unsigned int StartOffset)
{
	std::shared_ptr<CBHardVariables> returnValue(new CBufferOrthogonal(bytes, StartOffset));
	return returnValue;
}

//---------------------------------------------------------------------

CBufferWVP::CBufferWVP(std::vector<char>& bytes, const unsigned int StartOffset)
: CBHardVariables(bytes, StartOffset, sizeof(XMMATRIX))
{
}
void CBufferWVP::Update(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicObjectEntity> object)
{
	static const unsigned int sizeOfValue = this->sizeOfValue;
	const unsigned int copyStartingAt = this->StartOffset;

	if(object && camera)
	{
		XMFLOAT4X4 worldMatrix = object->GetWorld();
		XMFLOAT4X4 prespectiveMatrix = camera->GetPerspective();
		XMFLOAT4X4 viewMatrix = camera->GetView();

		XMMATRIX value = XMLoadFloat4x4(&worldMatrix) * XMLoadFloat4x4(&viewMatrix) * XMLoadFloat4x4(&prespectiveMatrix);

		value = XMMatrixTranspose(value);
		CHL::ByteCopy<XMMATRIX>(value, bytes, copyStartingAt);
	}
	else
	{
		XMMATRIX value = XMMatrixIdentity();
		value = XMMatrixTranspose(value);
		CHL::ByteCopy<XMMATRIX>(value, bytes, copyStartingAt);
	}
}
std::shared_ptr<CBHardVariables> CBufferWVP::Spawn(std::vector<char>& bytes, const unsigned int StartOffset)
{
	std::shared_ptr<CBHardVariables> returnValue(new CBufferWVP(bytes, StartOffset));
	return returnValue;
}

//---------------------------------------------------------------------

CBufferWVO::CBufferWVO(std::vector<char>& bytes, const unsigned int StartOffset)
: CBHardVariables(bytes, StartOffset, sizeof(XMMATRIX))
{
}
void CBufferWVO::Update(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicObjectEntity> object)
{
	static const unsigned int sizeOfValue = this->sizeOfValue;
	const unsigned int copyStartingAt = this->StartOffset;

	if(object && camera)
	{
		XMFLOAT4X4 worldMatrix = object->GetWorld();
		XMFLOAT4X4 prespectiveMatrix = camera->GetOrthogonal();
		XMFLOAT4X4 viewMatrix = camera->GetView();

		XMMATRIX value = XMLoadFloat4x4(&worldMatrix) * XMLoadFloat4x4(&viewMatrix) * XMLoadFloat4x4(&prespectiveMatrix);

		value = XMMatrixTranspose(value);
		CHL::ByteCopy<XMMATRIX>(value, bytes, copyStartingAt);
	}
	else
	{
		XMMATRIX value = XMMatrixIdentity();
		value = XMMatrixTranspose(value);
		CHL::ByteCopy<XMMATRIX>(value, bytes, copyStartingAt);
	}
}
std::shared_ptr<CBHardVariables> CBufferWVO::Spawn(std::vector<char>& bytes, const unsigned int StartOffset)
{
	std::shared_ptr<CBHardVariables> returnValue(new CBufferWVO(bytes, StartOffset));
	return returnValue;
}

//---------------------------------------------------------------------

CBufferEye::CBufferEye(std::vector<char>& bytes, const unsigned int StartOffset)
: CBHardVariables(bytes, StartOffset, sizeof(XMFLOAT4))
{
}
void CBufferEye::Update(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicObjectEntity> object)
{
	static const unsigned int sizeOfValue = this->sizeOfValue;
	const unsigned int copyStartingAt = this->StartOffset;

	if(camera)
	{
		XMFLOAT4 value = camera->GetEye();
		CHL::ByteCopy<XMFLOAT4>(value, bytes, copyStartingAt);
	}
	else
	{
		XMFLOAT4 value(0.0f, 0.0f, 0.0f, 1.0f);
		CHL::ByteCopy<XMFLOAT4>(value, bytes, copyStartingAt);
	}
}
std::shared_ptr<CBHardVariables> CBufferEye::Spawn(std::vector<char>& bytes, const unsigned int StartOffset)
{
	std::shared_ptr<CBHardVariables> returnValue(new CBufferEye(bytes, StartOffset));
	return returnValue;
}

//---------------------------------------------------------------------

std::unordered_map<std::string, VariableCreatorFunction> PopulateVariableTypes()
{
	std::unordered_map<std::string, VariableCreatorFunction> returnValue;

	returnValue[CBufferWorld::Name()] = CBufferWorld::Spawn;
	returnValue[CBufferView::Name()] = CBufferView::Spawn;
	returnValue[CBufferView2D::Name()] = CBufferView2D::Spawn;
	returnValue[CBufferPerspective::Name()] = CBufferPerspective::Spawn;
	returnValue[CBufferOrthogonal::Name()] = CBufferOrthogonal::Spawn;
	returnValue[CBufferWVP::Name()] = CBufferWVP::Spawn;
	returnValue[CBufferWVO::Name()] = CBufferWVO::Spawn;
	returnValue[CBufferEye::Name()] = CBufferEye::Spawn;

	return returnValue;
}

std::unordered_map<std::string, VariableCreatorFunction> VariableTypes = PopulateVariableTypes();

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