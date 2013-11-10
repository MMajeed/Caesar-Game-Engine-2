#ifndef __BasicDrawable__
#define __BasicDrawable__

#include "Linker.h"

#include "Drawable.h"
#include "Vertex.h"
#include "D3DShaderInfo.h"
#include <Model.h>
#include <string>
#include <D3D11.h>

class BasicDrawable : public Drawable
{
public:
	BasicDrawable(const std::string& inputID);
	virtual void Init();
	virtual void Destory();
	virtual void Update(double realTime, double deltaTime);
	virtual void Draw(TypedefObject::ObjectInfo& object);
	virtual std::shared_ptr<Drawable> clone() const;
	
	struct SpawnInfo
	{

	};
	static std::shared_ptr<BasicDrawable> Spawn(const std::string& inputID,
												const std::vector<Vertex>&	vectorVertices,
												const std::vector<WORD>&	vectorIndices,
												D3DShaderInfo				vertexFile,
												D3DShaderInfo				pixelFile,
												D3D11_CULL_MODE				cullMode,
												D3D11_FILL_MODE				fillMode,
												bool						bAntialiasedLine,
												bool						bMultisampleEnable);

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
		std::vector<Vertex>			vertices;
		std::vector<WORD>			indices;
		D3D11_CULL_MODE				cullMode;
		D3D11_FILL_MODE				fillMode; 
		bool						bAntialiasedLine;
		bool						bMultisampleEnable;
	} D3DInfo;

	virtual void InitVertexBuffer(ID3D11Device* device);
	virtual void InitIndexBuffer(ID3D11Device* device);
	virtual void InitInputLayout(ID3D11Device* device);
	virtual void InitVertexShader(ID3D11Device* device);
	virtual void InitPixelShader(ID3D11Device* device);
	virtual void InitRastersizerState(ID3D11Device* device);
	virtual void InitConstantBuffer(ID3D11Device* device);

	virtual void SetupDrawConstantBuffer(const TypedefObject::ObjectInfo& object);
	virtual void SetupDrawVertexBuffer(const TypedefObject::ObjectInfo& object);
	virtual void SetupDrawInputVertexShader(const TypedefObject::ObjectInfo& object);
	virtual void SetupDrawPixelShader(const TypedefObject::ObjectInfo& object);
	virtual void SetupDrawRasterizeShader(const TypedefObject::ObjectInfo& object);
	virtual void DrawObject(const TypedefObject::ObjectInfo& object);
	virtual void CleanupAfterDraw(const TypedefObject::ObjectInfo& object);

	virtual void ChangeRasterizerState(D3D11_CULL_MODE cullMode, D3D11_FILL_MODE fillMode, bool bAntialiasedLine, bool bMultisampleEnable);
protected:
	virtual void GetInfo(const TypedefObject::ObjectInfo& objec,
						 CHL::Vec4& location,
						 CHL::Vec4& rotation,
						 CHL::Vec4& scale,
						 CHL::Vec4& diffuse,
						 CHL::Vec4& ambient,
						 CHL::Vec4& spec);

};


#endif //__BasicDrawable__