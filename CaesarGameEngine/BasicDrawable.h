#ifndef __BasicDrawable__
#define __BasicDrawable__

#include "Drawable.h"
#include "Vertex.h"

#include <string>
#include <D3D11.h>

class BasicDrawable : public Drawable
{
public:
	BasicDrawable();
	virtual void Init();
	virtual void Clean();
	virtual void Update(float delta);
	virtual void Draw();
	virtual Drawable* clone() const;

	struct
	{
		ID3D11Buffer*				pVertexBuffer;
		ID3D11Buffer*				pIndexBuffer;
		ID3D11Buffer*				pConstantBuffer;
		ID3D11InputLayout*			pInputLayout;
		struct
		{
			std::string				FileName;
			std::string				EntryPoint;
			std::string				Model;
		}VertexShaderInfo;
		ID3D11VertexShader*			pVertexShader;
		struct
		{
			std::string				FileName;
			std::string				EntryPoint;
			std::string				Model;
		}PixelShaderInfo;
		ID3D11PixelShader*			pPixelShader;
		ID3D11RasterizerState*		pRastersizerState;
		std::string					textureFileName;
		ID3D11ShaderResourceView*	pTexture;
		std::vector<Vertex>			vertices;
		std::vector<WORD>			indices;
	} D3DInfo;

	virtual void InitVertexBuffer(ID3D11Device* device);
	virtual void InitIndexBuffer(ID3D11Device* device);
	virtual void InitInputLayout(ID3D11Device* device);
	virtual void InitVertexShader(ID3D11Device* device);
	virtual void InitPixelShader(ID3D11Device* device);
	virtual void InitRastersizerState(ID3D11Device* device);
	virtual void InitConstantBuffer(ID3D11Device* device);
	virtual void InitTexture(ID3D11Device* device);

	virtual void SetupDrawConstantBuffer();
	virtual void SetupDrawVertexBuffer();
	virtual void SetupDrawInputVertexShader();
	virtual void SetupDrawPixelShader();
	virtual void SetupDrawRasterizeShader();
	virtual void SetupDrawTexture();
	virtual void DrawObject();
	virtual void CleanupAfterDraw();
};


#endif //__BasicDrawable__