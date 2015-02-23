#include "GraphicSettingsFactory.h"

#include <Components.h>
#include <Message.h>
#include <Converter.h>
#include <Logger.h>
#include "GraphicManager.h"
#include "Scene.h"
#include "Resource.h"

void GraphicSettingsFactory::SetMainCamera(std::string cameraID)
{
	Components::Graphic->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Graphic->Mutex());

		Resource::DefaultCamera = cameraID;

		return Message::Status::Complete;
	});
}
void GraphicSettingsFactory::SetMainDrawSettings(std::string drawSettingsID)
{
	Components::Graphic->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Graphic->Mutex());

		Resource::DefaultDrawSettings = drawSettingsID;

		return Message::Status::Complete;
	});
}
void GraphicSettingsFactory::ChangeWindowsText(std::string s)
{
	Components::Graphic->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Graphic->Mutex());

		std::wstring ws = CHL::ToWString(s.c_str());
		SetWindowText(Resource::window.hWnd, ws.c_str());

		return Message::Status::Complete;
	});
}
void GraphicSettingsFactory::MoveWindow(unsigned int x, unsigned int y)
{
	Components::Graphic->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Graphic->Mutex());

		SetWindowPos(Resource::window.hWnd, 0, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		return Message::Status::Complete;
	});
}
void GraphicSettingsFactory::ResizeWindow(unsigned int height, unsigned int width)
{
	Components::Graphic->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Graphic->Mutex());

		GraphicManager& graphic = GraphicManager::GetInstance();
		graphic.ResizeWindow(width, height);

		return Message::Status::Complete;
	});
}
void GraphicSettingsFactory::ResizeClient(unsigned int height, unsigned int width)
{
	Components::Graphic->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Graphic->Mutex());

		GraphicManager& graphic = GraphicManager::GetInstance();
		graphic.ResizeClient(width, height);

		return Message::Status::Complete;
	});
}
void GraphicSettingsFactory::ResizeRender(unsigned int height, unsigned int width)
{
	Components::Graphic->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Graphic->Mutex());

		GraphicManager& graphic = GraphicManager::GetInstance();
		graphic.ResizeRender(width, height);

		return Message::Status::Complete;
	});
}
void GraphicSettingsFactory::DisableResize()
{
	Components::Graphic->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Graphic->Mutex());

		long dwStyle = GetWindowLong(Resource::window.hWnd, GWL_STYLE);
		dwStyle ^= WS_THICKFRAME;
		SetWindowLong(Resource::window.hWnd, GWL_STYLE, dwStyle);

		return Message::Status::Complete;
	});
}
void GraphicSettingsFactory::EnableResize()
{
	Components::Graphic->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Graphic->Mutex());

		long dwStyle = GetWindowLong(Resource::window.hWnd, GWL_STYLE);
		dwStyle |= WS_THICKFRAME;
		SetWindowLong(Resource::window.hWnd, GWL_STYLE, dwStyle);

		return Message::Status::Complete;
	});
}
void GraphicSettingsFactory::FullScreen()
{
	Components::Graphic->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Graphic->Mutex());

		Resource::D3DStuff.pSwapChain->SetFullscreenState(true, NULL);

		return Message::Status::Complete;
	});
}
void GraphicSettingsFactory::LeaveFullScreen()
{
	Components::Graphic->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Graphic->Mutex());

		Resource::D3DStuff.pSwapChain->SetFullscreenState(false, NULL);

		return Message::Status::Complete;
	});
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
	Components::Graphic->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Graphic->Mutex());

		Resource::D3DStuff.VSync = (int)v;

		return Message::Status::Complete;
	});
}