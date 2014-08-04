#include "CBHardVariables.h"

#include "XNAConverter.h"
#include "3DMath.h"
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

CBufferWorld2D::CBufferWorld2D(std::vector<char>& bytes, const unsigned int StartOffset) : CBHardVariables(bytes, StartOffset, sizeof(XMMATRIX))
{
}
void CBufferWorld2D::Update(const GraphicCameraEntity& camera, const GraphicObjectEntity& object)
{
	static const unsigned int sizeOfValue = this->sizeOfValue;
	const unsigned int copyStartingAt = this->StartOffset;

	auto window = GraphicManager::GetInstance().window;

	XMFLOAT4X4 animation = object.GetJointAnimation();
	XMFLOAT4X4 rigidBody = object.GetRigidBody();

	XMFLOAT4 location = object.GetLocation();

	location.x = location.x - window.width / 2.0f;
	location.y = (location.y * -1.0f) + (window.height / 2.0f);
	location.z = location.z;

	XMFLOAT4 rotation = object.GetRotation();
	XMFLOAT4 scale = object.GetScale();

	XMMATRIX xmTranslate = XMMatrixIdentity();
	XMMATRIX xmRotateX = XMMatrixIdentity();	XMMATRIX xmRotateY = XMMatrixIdentity();	XMMATRIX xmRotateZ = XMMatrixIdentity();
	XMMATRIX xmScaling = XMMatrixIdentity();
	XMMATRIX xmObjectFinal = XMMatrixIdentity();

	xmTranslate = XMMatrixTranslation(location.x, location.y, location.z);
	xmRotateX = XMMatrixRotationX(rotation.x + 3.14159265359f);
	xmRotateY = XMMatrixRotationY(rotation.y);
	xmRotateZ = XMMatrixRotationZ(rotation.z);

	xmScaling = XMMatrixScaling(scale.x, scale.y, scale.z);


	xmObjectFinal = XMMatrixMultiply(xmObjectFinal, xmScaling);
	xmObjectFinal = XMMatrixMultiply(xmObjectFinal, xmRotateX);
	xmObjectFinal = XMMatrixMultiply(xmObjectFinal, xmRotateY);
	xmObjectFinal = XMMatrixMultiply(xmObjectFinal, xmRotateZ);
	xmObjectFinal = XMMatrixMultiply(xmObjectFinal, xmTranslate);


	XMMATRIX value = xmObjectFinal;

	value = XMMatrixTranspose(value);

	CHL::ByteCopy<XMMATRIX>(value, bytes, copyStartingAt);
}
std::shared_ptr<CBHardVariables> CBufferWorld2D::Spawn(std::vector<char>& bytes, const unsigned int StartOffset)
{
	std::shared_ptr<CBHardVariables> returnValue(new CBufferWorld2D(bytes, StartOffset));
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

CBufferPerspective::CBufferPerspective(std::vector<char>& bytes, const unsigned int StartOffset)
: CBHardVariables(bytes, StartOffset, sizeof(XMMATRIX))
{
}
void CBufferPerspective::Update(const GraphicCameraEntity& camera, const GraphicObjectEntity& object)
{
	static const unsigned int sizeOfValue = this->sizeOfValue;
	const unsigned int copyStartingAt = this->StartOffset;

	XMFLOAT4X4 valueXM = camera.GetPerspective();
	XMMATRIX value = XMLoadFloat4x4(&valueXM);

	value = XMMatrixTranspose(value);
	memcpy(&bytes[copyStartingAt], &value, sizeOfValue);
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
void CBufferOrthogonal::Update(const GraphicCameraEntity& camera, const GraphicObjectEntity& object)
{
	static const unsigned int sizeOfValue = this->sizeOfValue;
	const unsigned int copyStartingAt = this->StartOffset;

	XMFLOAT4X4 valueXM = camera.GetOrthogonal();
	XMMATRIX value = XMLoadFloat4x4(&valueXM);

	value = XMMatrixTranspose(value);
	memcpy(&bytes[copyStartingAt], &value, sizeOfValue);
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
void CBufferWVP::Update(const GraphicCameraEntity& camera, const GraphicObjectEntity& object)
{
	static const unsigned int sizeOfValue = this->sizeOfValue;
	const unsigned int copyStartingAt = this->StartOffset;

	XMFLOAT4X4 worldMatrix = object.GetWorldTransformation();
	XMFLOAT4X4 prespectiveMatrix = camera.GetPerspective();
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

CBufferWVO::CBufferWVO(std::vector<char>& bytes, const unsigned int StartOffset)
: CBHardVariables(bytes, StartOffset, sizeof(XMMATRIX))
{
}
void CBufferWVO::Update(const GraphicCameraEntity& camera, const GraphicObjectEntity& object)
{
	static const unsigned int sizeOfValue = this->sizeOfValue;
	const unsigned int copyStartingAt = this->StartOffset;

	XMFLOAT4X4 worldMatrix = object.GetWorldTransformation();
	XMFLOAT4X4 prespectiveMatrix = camera.GetOrthogonal();
	XMFLOAT4X4 viewMatrix = camera.GetView();

	XMMATRIX value = XMLoadFloat4x4(&worldMatrix) * XMLoadFloat4x4(&viewMatrix) * XMLoadFloat4x4(&prespectiveMatrix);

	value = XMMatrixTranspose(value);
	CHL::ByteCopy<XMMATRIX>(value, bytes, copyStartingAt);
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
	returnValue[CBufferWorld2D::Name()] = CBufferWorld2D::Spawn;
	returnValue[CBufferView::Name()] = CBufferView::Spawn;
	returnValue[CBufferPerspective::Name()] = CBufferPerspective::Spawn;
	returnValue[CBufferOrthogonal::Name()] = CBufferOrthogonal::Spawn;
	returnValue[CBufferWVP::Name()] = CBufferWVP::Spawn;
	returnValue[CBufferWVO::Name()] = CBufferWVO::Spawn;
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