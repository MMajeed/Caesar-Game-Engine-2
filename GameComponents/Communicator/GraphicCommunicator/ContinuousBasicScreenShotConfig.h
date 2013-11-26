#ifndef __ContinuousBasicScreenShotConfig__
#define __ContinuousBasicScreenShotConfig__

#include "Linker.h"

#include <Message.h>
#include <string>
#include <Matrix.h>
#include <Vector.h>

namespace ContinuousBasicScreenShotConfig
{
	class AddContinuousBasicScreenShot : public Message
	{
	public:
		AddContinuousBasicScreenShot(unsigned int width, unsigned int height, const CHL::Matrix4x4& cameraMatrix, const CHL::Matrix4x4& prespectiveMatrix);

		Message::Status Work();

		CHL::Matrix4x4 camerMatrix;
		CHL::Matrix4x4 prespectiveMatrix;
		std::string newTextureID;
		std::string ID;
		unsigned int width;
		unsigned int height;
	};

	class ChangeCameraMatrix : public Message
	{
	public:
		ChangeCameraMatrix(const std::string& id, const CHL::Matrix4x4& camera);

		Message::Status Work();
		std::string ID;
		CHL::Matrix4x4 camerMatrix;
	};

	class ChangePrespectiveMatrix : public Message
	{
	public:
		ChangePrespectiveMatrix(const std::string& id, const CHL::Matrix4x4& prespective);

		Message::Status Work();
		std::string ID;
		CHL::Matrix4x4 prespective;
	};

};

#endif //__ContinuousBasicScreenShotConfig__