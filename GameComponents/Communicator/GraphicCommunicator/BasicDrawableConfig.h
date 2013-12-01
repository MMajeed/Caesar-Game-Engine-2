#ifndef __AddBasicDrawableMessage__
#define __AddBasicDrawableMessage__

#include "Linker.h"

#include <Message.h>
#include <Model.h>
#include <string>

namespace BasicDrawableConfig
{
	enum class CULL_MODE { CULL_NONE = 1, CULL_FRONT = 2, CULL_BACK = 3 };
	enum class FILL_MODE { FILL_WIREFRAME = 2, FILL_SOLID = 3 };

	class  AddBasicDrawableMessage : public Message
	{
	public:
		AddBasicDrawableMessage(const Model& model,
								std::string	vertexFileName,
								std::string	pixelFileName,
								CULL_MODE cullMode, 
								FILL_MODE fillMode);

		virtual Message::Status Work();

		Model model;
		std::string	vertexFileName;
		std::string	pixelFileName;
		CULL_MODE cullMode;
		FILL_MODE fillMode;

		std::string	ID;
	};

	class ChangeRastersizerState : public Message
	{
	public:
		std::string ID;
		CULL_MODE cullMode;
		FILL_MODE fillMode;

		ChangeRastersizerState(std::string ID, CULL_MODE cullMode, FILL_MODE fillMode);

		virtual Message::Status Work();
	};
};


#endif