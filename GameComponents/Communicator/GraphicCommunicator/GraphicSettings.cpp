#include "GraphicSettings.h"

#include <GraphicManager.h>

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

				if(graphic.D3DStuff.IsInitialized == true)
				{
					graphic.D3DStuff.pRenderTargetView->Release();
					graphic.D3DStuff.pDepthStencilBuffer->Release();
					graphic.D3DStuff.pDepthStencilView->Release();


					// Resize the swap chain and recreate the render target view.
					HRESULT hr = graphic.D3DStuff.pSwapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);
					if(FAILED(hr))
						throw std::runtime_error("Failed at resizing swap chain buffer");

					ID3D11Texture2D* pBuffer = NULL;
					hr = graphic.D3DStuff.pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBuffer);
					if(FAILED(hr))
						throw std::runtime_error("Failed at creating back buffer");

					hr = graphic.D3DStuff.pd3dDevice->CreateRenderTargetView(pBuffer, NULL, &graphic.D3DStuff.pRenderTargetView);
					if(FAILED(hr))
						throw std::runtime_error("Failed at creating Render Target view");

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
						throw std::runtime_error("Failed at creating dept buffer");
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
						throw std::runtime_error("Failed at creating depth stencil view");
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

				}
				return Message::Status::Complete;
			}

			unsigned int width;
			unsigned int height;
		};

		std::shared_ptr<OnResize> msg(new OnResize(widthInput, heightInput));
		GraphicManager::GetInstance().SubmitMessage(msg);
	}
}