#ifndef __AddBasicDrawableMessage__
#define __AddBasicDrawableMessage__

#include "Linker.h"

#include <Message.h>
#include <Model.h>
#include <string>

namespace BasicDrawableConfiguration
{
	class  AddBasicDrawableMessage : public Message
	{
	public:
		AddBasicDrawableMessage(const Model& model,
								std::string	vertexFileName,
								std::string	vertexEntryPoint,
								std::string	vertexModel,
								std::string	pixelFileName,
								std::string	pixelEntryPoint,
								std::string	pixelModel);

		virtual Message::Status Work();

		Model model;
		std::string	vertexFileName;
		std::string	vertexEntryPoint;
		std::string	vertexModel;
		std::string	pixelFileName;
		std::string	pixelEntryPoint;
		std::string	pixelModel;

		std::string	ID;
	};

	class ChangeRastersizerState : public Message
	{
	public:
		std::string ID;
		enum class CULL_MODE { CULL_NONE = 1, D3D11_CULL_FRONT = 2, D3D11_CULL_BACK = 3 } cullMode;
		enum class FILL_MODE { D3D11_FILL_WIREFRAME	= 2, D3D11_FILL_SOLID = 3 } fillMode;
		bool antialiasedLine;
		bool multisampleEnable;

		ChangeRastersizerState(std::string ID, CULL_MODE cullMode, FILL_MODE fillMode, bool antialiasedLine, bool multisampleEnable);

		virtual Message::Status Work();
	};
};


#endif