#ifndef __AddBasicDrawableMessage__
#define __AddBasicDrawableMessage__

#include "Linker.h"

#include <Message.h>
#include <Model.h>
#include <string>


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

#endif