#include "ShaderFactory.h"

#include <GenerateGUID.h>
#include <Components.h>
#include "Resource.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "GeometryShader.h"

std::string ShaderFactory::VertexCreate(std::string fileName)
{
	std::string ID = CHL::GenerateGUID();

	Components::Graphic->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Graphic->Mutex());

		std::shared_ptr<VertexShader> newObject = VertexShader::Spawn(fileName);
		Resource::VertexShaderList[ID] = newObject;

		return Message::Status::Complete;
	});

	return ID;
}
void ShaderFactory::VertexRelease(std::string ID)
{
	Components::Graphic->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Graphic->Mutex());

		Resource::VertexShaderList.erase(ID);

		return Message::Status::Complete;
	});
}

std::string ShaderFactory::PixelCreate(std::string fileName)
{
	std::string ID = CHL::GenerateGUID();

	Components::Graphic->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Graphic->Mutex());

		std::shared_ptr<PixelShader> newObject = PixelShader::Spawn(fileName);
		Resource::PixelShaderList[ID] = newObject;

		return Message::Status::Complete;
	});

	return ID;
}
void ShaderFactory::PixelRelease(std::string ID)
{
	Components::Graphic->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Graphic->Mutex());

		Resource::PixelShaderList.erase(ID);

		return Message::Status::Complete;
	});
}

std::string ShaderFactory::GeometryCreate(std::string fileName)
{
	std::string ID = CHL::GenerateGUID();

	Components::Graphic->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Graphic->Mutex());

		std::shared_ptr<GeometryShader> newObject = GeometryShader::Spawn(fileName);
		Resource::GeometryShaderList[ID] = newObject;

		return Message::Status::Complete;
	});

	return ID;
}
void ShaderFactory::GeometryRelease(std::string ID)
{

	Components::Graphic->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Graphic->Mutex());

		Resource::GeometryShaderList.erase(ID);

		return Message::Status::Complete;
	});
}