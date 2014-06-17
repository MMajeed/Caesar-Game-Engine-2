#ifndef __ScreenTexture__
#define __ScreenTexture__

#include "Linker.h"

#include "BasicTexture.h"
#include <vector>
#include "Vertex.h"

class GraphicComponentDLL_API ScreenTexture
{
protected:
	ScreenTexture();
public:
	virtual void Init();
	virtual void Destory();
	virtual void Draw(unsigned int width, unsigned int height, std::shared_ptr<BasicTexture> texture);

	static std::shared_ptr<ScreenTexture> Spawn();

	virtual ~ScreenTexture();

protected:
	struct ScreenTextureVertex
	{
		XMFLOAT3 Pos;
		XMFLOAT2 Texture;
	};
	struct ScreenTextureConstantBuffer
	{
		XMMATRIX WVP;
	};

	struct
	{
		ID3D11Buffer*				pVertexBuffer;
		ID3D11Buffer*				pIndexBuffer;
		ID3D11InputLayout*			pInputLayout;
		ID3D11VertexShader*			pVertexShader;
		ID3D11PixelShader*			pPixelShader;
		ID3D11RasterizerState* 		pRastersizerState;
		ID3D11Buffer*				pConstantBuffer;		
		std::vector<ScreenTextureVertex>	vertices;
		std::vector<WORD>					indices;
	} D3DInfo;

	virtual bool CheckIfValid(unsigned int width, unsigned int height, std::shared_ptr<BasicTexture> texture);
	virtual void SetupDepth(unsigned int width, unsigned int height, std::shared_ptr<BasicTexture> texture);
	virtual void SetupTexture(unsigned int width, unsigned int height, std::shared_ptr<BasicTexture> texture);
	virtual void SetupDrawConstantBuffer(unsigned int width, unsigned int height, std::shared_ptr<BasicTexture> texture);
	virtual void SetupDrawVertexBuffer(unsigned int width, unsigned int height, std::shared_ptr<BasicTexture> texture);
	virtual void SetupDrawInputVertexShader(unsigned int width, unsigned int height, std::shared_ptr<BasicTexture> texture);
	virtual void SetupDrawPixelShader(unsigned int width, unsigned int height, std::shared_ptr<BasicTexture> texture);
	virtual void SetupDrawGeometryShader(unsigned int width, unsigned int height, std::shared_ptr<BasicTexture> texture);
	virtual void SetupDrawRasterizeShader(unsigned int width, unsigned int height, std::shared_ptr<BasicTexture> texture);
	virtual void DrawObject(unsigned int width, unsigned int height, std::shared_ptr<BasicTexture> texture);
	virtual void CleanupAfterDraw(unsigned int width, unsigned int height, std::shared_ptr<BasicTexture> texture);

	virtual void InitVertexBuffer(ID3D11Device* device);
	virtual void InitIndexBuffer(ID3D11Device* device);
	virtual void InitInputLayout(ID3D11Device* device);
	virtual void InitVertexShader(ID3D11Device* device);
	virtual void InitPixelShader(ID3D11Device* device);
	virtual void InitRastersizerState(ID3D11Device* device);
	virtual void InitConstantBuffer(ID3D11Device* device);
};


#endif //__ScreenTexture__