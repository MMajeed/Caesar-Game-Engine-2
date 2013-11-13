#include "OnResize.h"
#include <GraphicManager.h>

OnResize::OnResize(unsigned int widthInput, unsigned int heightInput)
{
	this->width = widthInput;
	this->height = heightInput;
}

Message::Status OnResize::Work()
{
	GraphicManager& graphic = GraphicManager::GetInstance();

	if (graphic.direct3d.IsInitialized == true)
	{
		graphic.direct3d.pRenderTargetView->Release();
		graphic.direct3d.pDepthStencilBuffer->Release();
		graphic.direct3d.pDepthStencilView->Release();


		// Resize the swap chain and recreate the render target view.
		HRESULT hr = graphic.direct3d.pSwapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);
		if (FAILED(hr))
			throw std::exception("Failed at resizing swap chain buffer");

		ID3D11Texture2D* pBuffer = NULL;
		hr = graphic.direct3d.pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBuffer);
		if (FAILED(hr))
			throw std::exception("Failed at creating back buffer");

		hr = graphic.direct3d.pd3dDevice->CreateRenderTargetView(pBuffer, NULL, &graphic.direct3d.pRenderTargetView);
		if (FAILED(hr))
			throw std::exception("Failed at creating Render Target view");
	
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
		hr = graphic.direct3d.pd3dDevice->CreateTexture2D(&depthBufferDesc, NULL, &graphic.direct3d.pDepthStencilBuffer);
		if (FAILED(hr))
		{
			throw std::exception("Failed at creating dept buffer");
		}


		D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
		// Initialize the depth stencil view.
		ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

		// Set up the depth stencil view description.
		depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		depthStencilViewDesc.Texture2D.MipSlice = 0;

		// Create the depth stencil view.
		hr = graphic.direct3d.pd3dDevice->CreateDepthStencilView(graphic.direct3d.pDepthStencilBuffer, &depthStencilViewDesc, &graphic.direct3d.pDepthStencilView);
		if (FAILED(hr))
		{
			throw std::exception("Failed at creating depth stencil view");
		}

		graphic.direct3d.pImmediateContext->OMSetRenderTargets(1, &graphic.direct3d.pRenderTargetView, graphic.direct3d.pDepthStencilView);


		// Set the viewport transform.

		// Setup the viewport
		graphic.direct3d.vp.Width = (FLOAT)this->width;
		graphic.direct3d.vp.Height = (FLOAT)this->height;
		graphic.direct3d.vp.MinDepth = 0.0f;
		graphic.direct3d.vp.MaxDepth = 1.0f;
		graphic.direct3d.vp.TopLeftX = 0;
		graphic.direct3d.vp.TopLeftY = 0;
		graphic.direct3d.pImmediateContext->RSSetViewports(1, &(graphic.direct3d.vp));

	}
	return Message::Status::Complete;
}