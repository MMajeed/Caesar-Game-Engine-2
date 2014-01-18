#include "GraphicSettings.h"
#include <Converter.h>
#include <GraphicManager.h>
#include <Logger.h>

namespace GraphicSettings
{
	void Resize(unsigned int widthInput, unsigned int heightInput)
	{
		class OnResize : public Message
		{
		public:
			OnResize(unsigned int widthInput, unsigned int heightInput)
			{
				this->width = widthInput;
				this->height = heightInput;
			}

			virtual Message::Status Work()
			{
				GraphicManager& graphic = GraphicManager::GetInstance();

				std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

				if(graphic.D3DStuff.IsInitialized == true)
				{
					graphic.D3DStuff.pRenderTargetView->Release();
					graphic.D3DStuff.pDepthStencilBuffer->Release();
					graphic.D3DStuff.pDepthStencilView->Release();


					// Resize the swap chain and recreate the render target view.
					HRESULT hr = graphic.D3DStuff.pSwapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);
					if(FAILED(hr))
						Logger::LogError("Failed at resizing swap chain buffer");

					ID3D11Texture2D* pBuffer = NULL;
					hr = graphic.D3DStuff.pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBuffer);
					if(FAILED(hr))
						Logger::LogError("Failed at creating back buffer");

					hr = graphic.D3DStuff.pd3dDevice->CreateRenderTargetView(pBuffer, NULL, &graphic.D3DStuff.pRenderTargetView);
					if(FAILED(hr))
						Logger::LogError("Failed at creating Render Target view");

					pBuffer->Release();

					// Create the depth/stencil buffer and view.
					D3D11_TEXTURE2D_DESC depthBufferDesc;
					ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

					// Set up the description of the depth buffer.
					depthBufferDesc.Width = this->width;
					depthBufferDesc.Height = this->height;
					depthBufferDesc.MipLevels = 1;
					depthBufferDesc.ArraySize = 1;
					depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
					depthBufferDesc.SampleDesc.Count = 1;
					depthBufferDesc.SampleDesc.Quality = 0;
					depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
					depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
					depthBufferDesc.CPUAccessFlags = 0;
					depthBufferDesc.MiscFlags = 0;

					// Create the texture for the depth buffer using the filled out description.
					hr = graphic.D3DStuff.pd3dDevice->CreateTexture2D(&depthBufferDesc, NULL, &graphic.D3DStuff.pDepthStencilBuffer);
					if(FAILED(hr))
					{
						Logger::LogError("Failed at creating dept buffer");
					}


					D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
					// Initialize the depth stencil view.
					ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

					// Set up the depth stencil view description.
					depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
					depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
					depthStencilViewDesc.Texture2D.MipSlice = 0;

					// Create the depth stencil view.
					hr = graphic.D3DStuff.pd3dDevice->CreateDepthStencilView(graphic.D3DStuff.pDepthStencilBuffer, &depthStencilViewDesc, &graphic.D3DStuff.pDepthStencilView);
					if(FAILED(hr))
					{
						Logger::LogError("Failed at creating depth stencil view");
					}

					graphic.D3DStuff.pImmediateContext->OMSetRenderTargets(1, &graphic.D3DStuff.pRenderTargetView, graphic.D3DStuff.pDepthStencilView);


					// Set the viewport transform.

					// Setup the viewport
					graphic.D3DStuff.vp.Width = (FLOAT)this->width;
					graphic.D3DStuff.vp.Height = (FLOAT)this->height;
					graphic.D3DStuff.vp.MinDepth = 0.0f;
					graphic.D3DStuff.vp.MaxDepth = 1.0f;
					graphic.D3DStuff.vp.TopLeftX = 0;
					graphic.D3DStuff.vp.TopLeftY = 0;
					graphic.D3DStuff.pImmediateContext->RSSetViewports(1, &(graphic.D3DStuff.vp));

					graphic.window.width = this->width;
					graphic.window.height = this->height;
				}
				return Message::Status::Complete;
			}

			unsigned int width;
			unsigned int height;
		};

		std::shared_ptr<OnResize> msg(new OnResize(widthInput, heightInput));
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

				SetWindowPos(graphic.window.hWnd, 0, 0, 0, this->width, this->height, SWP_NOMOVE | SWP_NOZORDER);

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
				RECT rcClient, rcWind;
				POINT ptDiff;
				GetClientRect(graphic.window.hWnd, &rcClient);
				GetWindowRect(graphic.window.hWnd, &rcWind);
				ptDiff.x = (rcWind.right - rcWind.left) - rcClient.right;
				ptDiff.y = (rcWind.bottom - rcWind.top) - rcClient.bottom;

				SetWindowPos(graphic.window.hWnd, 0, 0, 0, width + ptDiff.x, height + ptDiff.y, SWP_NOMOVE | SWP_NOZORDER);

				return Message::Status::Complete;
			}

			unsigned int width;
			unsigned int height;
		};

		std::shared_ptr<Resize> msg(new Resize(height, width));
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
	void GetWindowsClientSize(unsigned int& height, unsigned int& width)
	{
		GraphicManager& graphic = GraphicManager::GetInstance();
		std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);
		height = graphic.window.height;
		width = graphic.window.width;
	}
	void GetWindowsWindowSize(unsigned int& height, unsigned int& width)
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
}