#include "GraphicSettingsFactory.h"

#include <Message.h>
#include <Converter.h>
#include <Logger.h>
#include "GraphicManager.h"
#include "Scene.h"
#include "Resource.h"

void GraphicSettingsFactory::SetMainCamera(std::string cameraID)
{
	class SetMainCameraMessage : public Message
	{
	public:
		SetMainCameraMessage(std::string cameraID) :
			cameraID(cameraID){}

		virtual Message::Status Work()
		{
			GraphicManager& graphic = GraphicManager::GetInstance();

			std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

			Resource::DefaultCamera = cameraID;

			return Message::Status::Complete;
		}
		std::string cameraID;
	};

	std::shared_ptr<SetMainCameraMessage> msg(new SetMainCameraMessage(cameraID));
	GraphicManager::GetInstance().SubmitMessage(msg);
}
void GraphicSettingsFactory::SetMainDrawSettings(std::string drawSettingsID)
{
	class SetMainDrawSettingsMessage : public Message
	{
	public:
		SetMainDrawSettingsMessage(std::string DrawSettingsID) :
			DrawSettingsID(DrawSettingsID){}

		virtual Message::Status Work()
		{
			GraphicManager& graphic = GraphicManager::GetInstance();

			std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

			Resource::DefaultDrawSettings = DrawSettingsID;

			return Message::Status::Complete;
		}
		std::string DrawSettingsID;
	};

	std::shared_ptr<SetMainDrawSettingsMessage> msg(new SetMainDrawSettingsMessage(drawSettingsID));
	GraphicManager::GetInstance().SubmitMessage(msg);
}
void GraphicSettingsFactory::ChangeWindowsText(std::string s)
{
	class SetTitle : public Message
	{
	public:
		SetTitle(std::string s)
		{
			this->title = s;
		}

		virtual Message::Status Work()
		{
			GraphicManager& graphic = GraphicManager::GetInstance();
			std::lock_guard<std::mutex> lock(graphic.mutex);
			std::wstring ws = CHL::ToWString(title.c_str());
			SetWindowText(Resource::window.hWnd, ws.c_str());
			return Message::Status::Complete;
		}

		std::string title;
	};

	std::shared_ptr<SetTitle> msg(new SetTitle(s));
	GraphicManager::GetInstance().SubmitMessage(msg);
}
void GraphicSettingsFactory::MoveWindow(unsigned int x, unsigned int y)
{
	class Move : public Message
	{
	public:
		Move(unsigned int x, unsigned int y)
		{
			this->x = x;
			this->y = y;
		}

		virtual Message::Status Work()
		{
			GraphicManager& graphic = GraphicManager::GetInstance();

			std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

			SetWindowPos(Resource::window.hWnd, 0, this->x, this->y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

			return Message::Status::Complete;
		}

		unsigned int x;
		unsigned int y;
	};

	std::shared_ptr<Move> msg(new Move(x, y));
	GraphicManager::GetInstance().SubmitMessage(msg);
}
void GraphicSettingsFactory::ResizeWindow(unsigned int height, unsigned int width)
{
	class Resize : public Message
	{
	public:
		Resize(unsigned int height, unsigned int width)
		{
			this->width = width;
			this->height = height;
		}

		virtual Message::Status Work()
		{
			GraphicManager& graphic = GraphicManager::GetInstance();

			std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

			graphic.ResizeWindow(this->width, this->height);

			return Message::Status::Complete;
		}

		unsigned int width;
		unsigned int height;
	};

	std::shared_ptr<Resize> msg(new Resize(height, width));
	GraphicManager::GetInstance().SubmitMessage(msg);
}
void GraphicSettingsFactory::ResizeClient(unsigned int height, unsigned int width)
{
	class Resize : public Message
	{
	public:
		Resize(unsigned int height, unsigned int width)
		{
			this->width = width;
			this->height = height;
		}

		virtual Message::Status Work()
		{
			GraphicManager& graphic = GraphicManager::GetInstance();

			std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

			graphic.ResizeClient(this->width, this->height);

			return Message::Status::Complete;
		}

		unsigned int width;
		unsigned int height;
	};

	std::shared_ptr<Resize> msg(new Resize(height, width));
	GraphicManager::GetInstance().SubmitMessage(msg);
}
void GraphicSettingsFactory::ResizeRender(unsigned int height, unsigned int width)
{
	class ResizeRenderMessage : public Message
	{
	public:
		ResizeRenderMessage(unsigned int height, unsigned int width)
		{
			this->width = width;
			this->height = height;
		}

		virtual Message::Status Work()
		{
			GraphicManager& graphic = GraphicManager::GetInstance();

			std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);
			graphic.ResizeRender(width, height);

			return Message::Status::Complete;
		}

		unsigned int width;
		unsigned int height;
	};

	std::shared_ptr<ResizeRenderMessage> msg(new ResizeRenderMessage(height, width));
	GraphicManager::GetInstance().SubmitMessage(msg);
}
void GraphicSettingsFactory::DisableResize()
{
	class Resize : public Message
	{
	public:
		Resize(){}

		virtual Message::Status Work()
		{
			GraphicManager& graphic = GraphicManager::GetInstance();

			std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);
			long dwStyle = GetWindowLong(Resource::window.hWnd, GWL_STYLE);
			dwStyle ^= WS_THICKFRAME;
			SetWindowLong(Resource::window.hWnd, GWL_STYLE, dwStyle);
			return Message::Status::Complete;
		}
	};

	std::shared_ptr<Resize> msg(new Resize());
	GraphicManager::GetInstance().SubmitMessage(msg);
}
void GraphicSettingsFactory::EnableResize()
{
	class Resize : public Message
	{
	public:
		Resize(){}

		virtual Message::Status Work()
		{
			GraphicManager& graphic = GraphicManager::GetInstance();

			std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);
			long dwStyle = GetWindowLong(Resource::window.hWnd, GWL_STYLE);
			dwStyle |= WS_THICKFRAME;
			SetWindowLong(Resource::window.hWnd, GWL_STYLE, dwStyle);
			return Message::Status::Complete;
		}
	};

	std::shared_ptr<Resize> msg(new Resize());
	GraphicManager::GetInstance().SubmitMessage(msg);
}
void GraphicSettingsFactory::FullScreen()
{
	class Full : public Message
	{
	public:
		Full(){	}

		virtual Message::Status Work()
		{
			GraphicManager& graphic = GraphicManager::GetInstance();

			std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);
			Resource::D3DStuff.pSwapChain->SetFullscreenState(true, NULL);
			return Message::Status::Complete;
		}
	};

	std::shared_ptr<Full> msg(new Full());
	GraphicManager::GetInstance().SubmitMessage(msg);
}
void GraphicSettingsFactory::LeaveFullScreen()
{
	class LeaveFull : public Message
	{
	public:
		LeaveFull(){	}

		virtual Message::Status Work()
		{
			GraphicManager& graphic = GraphicManager::GetInstance();

			std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);
			Resource::D3DStuff.pSwapChain->SetFullscreenState(false, NULL);
			return Message::Status::Complete;
		}
	};

	std::shared_ptr<LeaveFull> msg(new LeaveFull());
	GraphicManager::GetInstance().SubmitMessage(msg);
}
bool GraphicSettingsFactory::IsFullScreen()
{
	GraphicManager& graphic = GraphicManager::GetInstance();

	std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);
	BOOL status = false;
	Resource::D3DStuff.pSwapChain->GetFullscreenState(&status, NULL);
	return status != 0;
}
void GraphicSettingsFactory::GetClientSize(unsigned int& height, unsigned int& width)
{
	GraphicManager& graphic = GraphicManager::GetInstance();
	std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);
	height = Resource::window.height;
	width = Resource::window.width;
}
void GraphicSettingsFactory::GetWindowSize(unsigned int& height, unsigned int& width)
{
	GraphicManager& graphic = GraphicManager::GetInstance();
	std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);
	RECT rect;
	if(GetWindowRect(Resource::window.hWnd, &rect))
	{
		width = rect.right - rect.left;
		height = rect.bottom - rect.top;
	}
}
void GraphicSettingsFactory::GetRenderSize(unsigned int& height, unsigned int& width)
{
	GraphicManager& graphic = GraphicManager::GetInstance();
	std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);
	height = (unsigned int)Resource::D3DStuff.vp.Height;
	width = (unsigned int)Resource::D3DStuff.vp.Width;
}
void GraphicSettingsFactory::GetWindowsLocation(unsigned int& x, unsigned int& y)
{
	GraphicManager& graphic = GraphicManager::GetInstance();
	if(GraphicSettingsFactory::IsFullScreen() == true)
	{
		x = 0;
		y = 0;
	}
	else
	{
		std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);
		RECT rect;
		GetWindowRect(Resource::window.hWnd, &rect);
		x = rect.left;
		y = rect.top;
	}
}
void GraphicSettingsFactory::GetPosRelativeToClient(int& x, int& y)
{
	GraphicManager& graphic = GraphicManager::GetInstance();
	POINT p{x, y};
	std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);
	if(ScreenToClient(Resource::window.hWnd, &p) != 0)
	{
		x = p.x;
		y = p.y;
	}
	else
	{
		x = -1;
		y = -1;
	}
}
void GraphicSettingsFactory::VSync(bool v)
{
	class VSyncMessage : public Message
	{
	public:
		VSyncMessage(bool v) :
			v(v){}

		virtual Message::Status Work()
		{
			GraphicManager& graphic = GraphicManager::GetInstance();

			std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

			Resource::D3DStuff.VSync = (int)v;

			return Message::Status::Complete;
		}
		bool v;
	};

	std::shared_ptr<VSyncMessage> msg(new VSyncMessage(v));
	GraphicManager::GetInstance().SubmitMessage(msg);
}