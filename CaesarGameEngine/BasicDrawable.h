#ifndef __BasicDrawable__
#define __BasicDrawable__

#include "Drawable.h"
#include "Vertex.h"
#include "D3DShaderInfo.h"
#include "Model.h"

#include <string>
#include <D3D11.h>

class BasicDrawable : public Drawable
{
public:
	BasicDrawable(std::string newID);
	virtual void Init();
	virtual void Clean();
	virtual void Update(float delta);
	virtual void Draw(std::shared_ptr<Object> object);
	virtual std::shared_ptr<Drawable> clone() const;
	
	static std::shared_ptr<BasicDrawable> Spawn(std::string					id,
												const std::vector<Vertex>&	vectorVertices,
												const std::vector<WORD>&	vectorIndices,
												D3DShaderInfo				vertexFile,
												D3DShaderInfo				pixelFile,
												std::string					textureFileName = "");

	struct
	{
		ID3D11Buffer*				pVertexBuffer;
		ID3D11Buffer*				pIndexBuffer;
		ID3D11Buffer*				pConstantBuffer;
		ID3D11InputLayout*			pInputLayout;
		D3DShaderInfo				VertexShaderInfo;
		ID3D11VertexShader*			pVertexShader;
		D3DShaderInfo				PixelShaderInfo;
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

	virtual void SetupDrawConstantBuffer(std::shared_ptr<Object> object);
	virtual void SetupDrawVertexBuffer(std::shared_ptr<Object> object);
	virtual void SetupDrawInputVertexShader(std::shared_ptr<Object> object);
	virtual void SetupDrawPixelShader(std::shared_ptr<Object> object);
	virtual void SetupDrawRasterizeShader(std::shared_ptr<Object> object);
	virtual void SetupDrawTexture(std::shared_ptr<Object> object);
	virtual void DrawObject(std::shared_ptr<Object> object);
	virtual void CleanupAfterDraw(std::shared_ptr<Object> object);


};


#endif //__BasicDrawable__