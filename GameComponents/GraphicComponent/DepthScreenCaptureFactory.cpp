#include "DepthScreenCaptureFactory.h"

#include <GenerateGUID.h>
#include "Resource.h"
#include "GraphicManager.h"
#include "DepthScreenCapture.h"
#include "BasicTexture.h"

void DepthScreenCaptureFactory::Create(unsigned int width,
									   unsigned int height,
									   unsigned int priority,
									   const std::string& cameraID,
									   const std::string& drawSettingsID,
									   std::string& ID,
									   std::string& textureID)
{
		class AddDepthScreenCapture : public Message
		{
		public:
			AddDepthScreenCapture(unsigned int width,
								  unsigned int height,
								  unsigned int priority,
								  const std::string& cameraID,
								  const std::string& drawSettingsID)
			{
				this->width = width;
				this->height = height;
				this->priority = priority;
				this->cameraID = cameraID;
				this->drawSettingsID = drawSettingsID;
				this->newTextureID = CHL::GenerateGUID();
				this->ID = CHL::GenerateGUID();
			}

			Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

				std::shared_ptr<BasicTexture> newTexture =
					BasicTexture::Spawn();
				Resource::TextureList[this->newTextureID] =  newTexture;

				std::shared_ptr<DepthScreenCapture> newDepthScreenShot =
					DepthScreenCapture::Spawn(this->newTextureID, this->width, this->height, this->priority, this->cameraID, this->drawSettingsID);
				Resource::ScreenCaptureList[this->ID] = newDepthScreenShot;

				return Message::Status::Complete;
			}


			std::string cameraID;
			std::string drawSettingsID;
			std::string newTextureID;
			std::string ID;
			unsigned int width;
			unsigned int height;
			unsigned int priority;
		};
		std::shared_ptr<AddDepthScreenCapture> msg
			(new AddDepthScreenCapture(width, height, priority, cameraID, drawSettingsID));
		GraphicManager::GetInstance().SubmitMessage(msg);
		ID = msg->ID;
		textureID = msg->newTextureID;
}
void DepthScreenCaptureFactory::SetCameraID(const std::string& id, const std::string& cameraid)
{
	class ChangeEye : public Message
	{
	public:
		ChangeEye(const std::string& id, const std::string& cameraID)
		{
			this->ID = id;
			this->cameraID = cameraID;
		}

		Message::Status Work()
		{
			std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

			auto screenCapture = Resource::ScreenCaptureList.find(this->ID);
			if(screenCapture != Resource::ScreenCaptureList.end())
			{
				std::shared_ptr<DepthScreenCapture> cast = std::dynamic_pointer_cast<DepthScreenCapture>(screenCapture->second);
				if(cast)
				{
					cast->cameraID = this->cameraID;
				}
			}

			return Message::Status::Complete;
		}
		std::string ID;
		std::string cameraID;
	};

	std::shared_ptr<ChangeEye> msg
		(new ChangeEye(id, cameraid));
	GraphicManager::GetInstance().SubmitMessage(msg);
}
void DepthScreenCaptureFactory::SetDrawSettingsID(const std::string& id, const std::string& dsID)
{
	class ChangeDrawSettingsMessage : public Message
	{
	public:
		ChangeDrawSettingsMessage(const std::string& id, const std::string& DrawSettingsID)
		{
			this->ID = id;
			this->DrawSettingsID = DrawSettingsID;
		}

		Message::Status Work()
		{
			std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

			auto screenCapture = Resource::ScreenCaptureList.find(this->ID);
			if(screenCapture != Resource::ScreenCaptureList.end())
			{
				std::shared_ptr<DepthScreenCapture> cast = std::dynamic_pointer_cast<DepthScreenCapture>(screenCapture->second);
				if(cast)
				{
					cast->drawSettingsID = this->DrawSettingsID;
				}
			}

			return Message::Status::Complete;
		}
		std::string ID;
		std::string DrawSettingsID;
	};

	std::shared_ptr<ChangeDrawSettingsMessage> msg
		(new ChangeDrawSettingsMessage(id, dsID));
	GraphicManager::GetInstance().SubmitMessage(msg);
}
void DepthScreenCaptureFactory::SetPriority(const std::string& id, int p)
{
	class SetPriorityMessage : public Message
	{
	public:
		SetPriorityMessage(const std::string& id, int p)
		{
			this->ID = id;
			this->p = p;
		}

		Message::Status Work()
		{
			std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

			auto screenCapture = Resource::ScreenCaptureList.find(this->ID);
			if(screenCapture != Resource::ScreenCaptureList.end())
			{
				std::shared_ptr<DepthScreenCapture> cast = std::dynamic_pointer_cast<DepthScreenCapture>(screenCapture->second);
				if(cast)
				{
					cast->Priority = this->p;
				}
			}

			return Message::Status::Complete;
		}
		std::string ID;
		int p;
	};

	std::shared_ptr<SetPriorityMessage> msg
		(new SetPriorityMessage(id, p));
	GraphicManager::GetInstance().SubmitMessage(msg);
}
void DepthScreenCaptureFactory::Release(std::string ID)
{
	class ReleaseCapture : public Message
	{
	public:
		std::string ID;
		ReleaseCapture(std::string ID)
		{
			this->ID = ID;
		}

		virtual Message::Status Work()
		{
			std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

			Resource::ScreenCaptureList.erase(this->ID);

			return Message::Status::Complete;
		}
	};

	std::shared_ptr<ReleaseCapture> msg
		(new ReleaseCapture(ID));
	GraphicManager::GetInstance().SubmitMessage(msg);
}