#ifndef __AddBasicDrawableMessage__
#define __AddBasicDrawableMessage__

#include "Message.h"
#include "Model.h"
#include "Vertex.h"
#include "D3DShaderInfo.h"
#include <string>


class AddBasicDrawableMessage : public Message
{
public:
	AddBasicDrawableMessage(const Model& model,
						    std::string	vertexFileName,
							std::string	vertexEntryPoint,
							std::string	vertexModel,
							std::string	pixelFileName,
							std::string	pixelEntryPoint,
							std::string	pixelModel,
							std::string texture = "");

	virtual Message::Status Work();

	std::string			ID;
	std::vector<Vertex> vectorVertices;
	std::vector<WORD>	vectorIndices;
	D3DShaderInfo		vertexFile;
	D3DShaderInfo		pixelFile;
	std::string			textureFileName;
};

#endif