#include "GraphicSettings.h"
#include <Message.h>
#include <Converter.h>
#include <GraphicManager.h>
#include <Logger.h>
#include <Scene.h>

namespace GraphicSettings
{
	void SetMainCamera(std::string cameraID)
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

				graphic.DefaultCamera = cameraID;

				return Message::Status::Complete;
			}
			std::string cameraID;
		};

		std::shared_ptr<SetMainCameraMessage> msg(new SetMainCameraMessage(cameraID));
		GraphicManager::GetInstance().SubmitMessage(msg);
	}
	GraphicCommunicatorDLL_API void SetMainDrawSettings(std::string drawSettingsID)
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

				graphic.DefaultDrawSettings = DrawSettingsID;

				return Message::Status::Complete;
			}
			std::string DrawSettingsID;
		};

		std::shared_ptr<SetMainDrawSettingsMessage> msg(new SetMainDrawSettingsMessage(drawSettingsID));
		GraphicManager::GetInstance().SubmitMessage(msg);
	}
	void ChangeWindowsText(std::string s)
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
				SetWindowText(graphic.window.hWnd, ws.c_str());
				return Message::Status::Complete;
			}

			std::string title;
		};

		std::shared_ptr<SetTitle> msg(new SetTitle(s));
		GraphicManager::GetInstance().SubmitMessage(msg);
	}
	void MoveWindow(unsigned int x, unsigned int y)
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

				SetWindowPos(graphic.window.hWnd, 0, this->x, this->y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
				
				return Message::Status::Complete;
			}

			unsigned int x;
			unsigned int y;
		}; 
		
		std::shared_ptr<Move> msg(new Move(x, y));
		GraphicManager::GetInstance().SubmitMessage(msg);
	}
	void ResizeWindow(unsigned int height, unsigned int width)
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
	void ResizeClient(unsigned int height, unsigned int width)
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
	void ResizeRender(unsigned int height, unsigned int width)
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
	void DisableResize()
	{
		class Resize : public Message
		{
		public:
			Resize(){}

			virtual Message::Status Work()
			{
				GraphicManager& graphic = GraphicManager::GetInstance();

				std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);
				long dwStyle = GetWindowLong(graphic.window.hWnd, GWL_STYLE);
				dwStyle ^= WS_THICKFRAME;
				SetWindowLong(graphic.window.hWnd, GWL_STYLE, dwStyle);
				return Message::Status::Complete;
			}
		};

		std::shared_ptr<Resize> msg(new Resize());
		GraphicManager::GetInstance().SubmitMessage(msg);
	}
	void EnableResize()

	{
		class Resize : public Message
		{
		public:
			Resize(){}

			virtual Message::Status Work()
			{
				GraphicManager& graphic = GraphicManager::GetInstance();

				std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);
				long dwStyle = GetWindowLong(graphic.window.hWnd, GWL_STYLE);
				dwStyle |= WS_THICKFRAME;
				SetWindowLong(graphic.window.hWnd, GWL_STYLE, dwStyle);
				return Message::Status::Complete;
			}
		};

		std::shared_ptr<Resize> msg(new Resize());
		GraphicManager::GetInstance().SubmitMessage(msg);
	}
	void FullScreen()
	{
		class Full : public Message
		{
		public:
			Full(){	}

			virtual Message::Status Work()
			{
				GraphicManager& graphic = GraphicManager::GetInstance();

				std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);
				graphic.D3DStuff.pSwapChain->SetFullscreenState(true, NULL);
				return Message::Status::Complete;
			}
		};

		std::shared_ptr<Full> msg(new Full());
		GraphicManager::GetInstance().SubmitMessage(msg);
	}
	void LeaveFullScreen()
	{
		class LeaveFull : public Message
		{
		public:
			LeaveFull(){	}

			virtual Message::Status Work()
			{
				GraphicManager& graphic = GraphicManager::GetInstance();

				std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);
				graphic.D3DStuff.pSwapChain->SetFullscreenState(false, NULL);
				return Message::Status::Complete;
			}
		};

		std::shared_ptr<LeaveFull> msg(new LeaveFull());
		GraphicManager::GetInstance().SubmitMessage(msg);
	}
	bool IsFullScreen()
	{
		GraphicManager& graphic = GraphicManager::GetInstance();

		std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);
		BOOL status = false;
		graphic.D3DStuff.pSwapChain->GetFullscreenState(&status, NULL);
		return status != 0; 
	}
	void GetClientSize(unsigned int& height, unsigned int& width)
	{
		GraphicManager& graphic = GraphicManager::GetInstance();
		std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);
		height = graphic.window.height;
		width = graphic.window.width;
	}
	void GetWindowSize(unsigned int& height, unsigned int& width)
	{
		GraphicManager& graphic = GraphicManager::GetInstance();
		std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);
		RECT rect;
		if(GetWindowRect(graphic.window.hWnd, &rect))
		{
			width = rect.right - rect.left;
			height = rect.bottom - rect.top;
		}
	}
	void GetRenderSize(unsigned int& height, unsigned int& width)
	{
		GraphicManager& graphic = GraphicManager::GetInstance();
		std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);
		height = (unsigned int)graphic.D3DStuff.vp.Height;
		width = (unsigned int)graphic.D3DStuff.vp.Width;
	}
	void GetWindowsLocation(unsigned int& x, unsigned int& y)
	{
		GraphicManager& graphic = GraphicManager::GetInstance();
		if(GraphicSettings::IsFullScreen() == true)
		{
			x = 0;
			y = 0;
		}
		else
		{
			std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);
			RECT rect;
			GetWindowRect(graphic.window.hWnd, &rect);
			x = rect.left;
			y = rect.top;
		}
	}
	void GetPosRelativeToClient(int& x, int& y)
	{
		GraphicManager& graphic = GraphicManager::GetInstance();
		POINT p{x, y};
		std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);
		if(ScreenToClient(graphic.window.hWnd, &p) != 0)
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
	void VSync(bool v)
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

				graphic.D3DStuff.VSync = (int)v;

				return Message::Status::Complete;
			}
			bool v;
		};

		std::shared_ptr<VSyncMessage> msg(new VSyncMessage(v));
		GraphicManager::GetInstance().SubmitMessage(msg);
	}
}