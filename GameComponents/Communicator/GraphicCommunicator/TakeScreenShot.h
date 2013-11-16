#ifndef __TakeScreenShot__
#define __TakeScreenShot__

#include "Linker.h"

#include <Message.h>
#include <string>
#include <Matrix.h>
#include <Vector.h>

class TakeBasicScreenShot : public Message
{
public:
	TakeBasicScreenShot(unsigned int width, unsigned int height, const CHL::Matrix4x4& cameraMatrix, const CHL::Matrix4x4& prespectiveMatrix);

	Message::Status Work();

	CHL::Matrix4x4 camerMatrix;
	CHL::Matrix4x4 prespectiveMatrix;
	std::string newTextureID;
	unsigned int width;
	unsigned int height;
};

class TakeDepthScreenShot : public Message
{
public:
	TakeDepthScreenShot(unsigned int width, unsigned int height, const CHL::Matrix4x4& cameraMatrix, const CHL::Matrix4x4& prespectiveMatrix);

	Message::Status Work();

	CHL::Matrix4x4 camerMatrix;
	CHL::Matrix4x4 prespectiveMatrix;
	std::string newTextureID;
	unsigned int width;
	unsigned int height;
};

class TakeCubeScreenShot : public Message
{
public:
	TakeCubeScreenShot(unsigned int width, unsigned int height, const CHL::Vec4& eye);

	Message::Status Work();

	CHL::Vec4 eye;
	std::string newTextureID;
	unsigned int width;
	unsigned int height;
};


#endif //__TakeScreenShot__