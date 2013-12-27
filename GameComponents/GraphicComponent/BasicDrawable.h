#ifndef __BasicDrawable__
#define __BasicDrawable__

#include "Linker.h"

#include "Drawable.h"
#include "Vertex.h"
#include <Model.h>
#include <string>
#include <D3D11.h>

class BasicDrawable : public Drawable
{
public:
	BasicDrawable();
	virtual void Init();
	virtual void Destory();
	virtual void Update(double realTime, double deltaTime);
	virtual void Draw(std::shared_ptr<ObjectINFO> object, const SceneInfo& si);
	virtual void DrawShadow(std::shared_ptr<ObjectINFO> object, const SceneInfo& si);
	virtual std::shared_ptr<Drawable> clone() const;
	
	static std::shared_ptr<BasicDrawable> Spawn(const std::vector<Vertex>&	vectorVertices,
												const std::vector<WORD>&	vectorIndices,
												const std::string&			vertexFile,
												const std::string&			pixelFile,
												D3D11_CULL_MODE				cullMode,
												D3D11_FILL_MODE				fillMode);

	struct
	{
		ID3D11Buffer*				pVertexBuffer;
		ID3D11Buffer*				pIndexBuffer;
		ID3D11InputLayout*			pInputLayout;
		std::string					VertexShaderInfo;
		ID3D11VertexShader*			pVertexShader;
		std::string					PixelShaderInfo;
		ID3D11PixelShader*			pPixelShader;
		ID3D11RasterizerState*		pRastersizerState;
		ID3D11RasterizerState*		pShadowRastersizerState;
		std::vector<Vertex>			vertices;
		std::vector<WORD>			indices;
		D3D11_CULL_MODE				cullMode;
		D3D11_FILL_MODE				fillMode;
	} D3DInfo;

	virtual void InitVertexBuffer(ID3D11Device* device);
	virtual void InitIndexBuffer(ID3D11Device* device);
	virtual void InitInputLayout(ID3D11Device* device);
	virtual void InitVertexShader(ID3D11Device* device);
	virtual void InitPixelShader(ID3D11Device* device);
	virtual void InitRastersizerState(ID3D11Device* device);
	virtual void InitShadowRastersizerState(ID3D11Device* device);

	virtual bool CheckIfValid(const std::shared_ptr<ObjectINFO>& object, const SceneInfo& si);
	virtual void SetupDepth(const std::shared_ptr<ObjectINFO>& object, const SceneInfo& si);
	virtual void SetupTexture(const std::shared_ptr<ObjectINFO>& object, const SceneInfo& si);
	virtual void SetupDrawConstantBuffer(const std::shared_ptr<ObjectINFO>& object, const SceneInfo& si);
	virtual void SetupDrawVertexBuffer(const std::shared_ptr<ObjectINFO>& object, const SceneInfo& si);
	virtual void SetupDrawInputVertexShader(const std::shared_ptr<ObjectINFO>& object, const SceneInfo& si);
	virtual void SetupDrawPixelShader(const std::shared_ptr<ObjectINFO>& object, const SceneInfo& si);
	virtual void SetupDrawRasterizeShader(const std::shared_ptr<ObjectINFO>& object, const SceneInfo& si);
	virtual void DrawObject(const std::shared_ptr<ObjectINFO>& object, const SceneInfo& si);
	virtual void CleanupAfterDraw(const std::shared_ptr<ObjectINFO>& object, const SceneInfo& si);

	virtual void CalculateWVP(const std::shared_ptr<ObjectINFO>& object, const SceneInfo& si, XMFLOAT4X4& worldFloat4x4, XMFLOAT4X4& finalFloat4x4);

	virtual void ChangeRasterizerState(D3D11_CULL_MODE cullMode, D3D11_FILL_MODE fillMode);
	virtual void ChangeModel(const std::vector<Vertex>&	vectorVertices,
							 const std::vector<WORD>&	vectorIndices);
};


#endif //__BasicDrawable__