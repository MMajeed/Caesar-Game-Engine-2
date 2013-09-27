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
	BasicDrawable();
	virtual void Init();
	virtual void Destory();
	virtual void Update(float delta);
	virtual void Draw(const CHL::MapQ<std::string, std::string>& object);
	virtual std::shared_ptr<Drawable> clone() const;
	
	static std::shared_ptr<BasicDrawable> Spawn(const std::vector<Vertex>&	vectorVertices,
												const std::vector<WORD>&	vectorIndices,
												D3DShaderInfo				vertexFile,
												D3DShaderInfo				pixelFile);

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
	} D3DInfo;

	virtual void InitVertexBuffer(ID3D11Device* device);
	virtual void InitIndexBuffer(ID3D11Device* device);
	virtual void InitInputLayout(ID3D11Device* device);
	virtual void InitVertexShader(ID3D11Device* device);
	virtual void InitPixelShader(ID3D11Device* device);
	virtual void InitRastersizerState(ID3D11Device* device);
	virtual void InitConstantBuffer(ID3D11Device* device);

	virtual void SetupDrawConstantBuffer(const CHL::MapQ<std::string, std::string>& object);
	virtual void SetupDrawVertexBuffer(const CHL::MapQ<std::string, std::string>& object);
	virtual void SetupDrawInputVertexShader(const CHL::MapQ<std::string, std::string>& object);
	virtual void SetupDrawPixelShader(const CHL::MapQ<std::string, std::string>& object);
	virtual void SetupDrawRasterizeShader(const CHL::MapQ<std::string, std::string>& object);
	virtual void DrawObject(const CHL::MapQ<std::string, std::string>& object);
	virtual void CleanupAfterDraw(const CHL::MapQ<std::string, std::string>& object);

protected:
	virtual void GetInfo(const CHL::MapQ<std::string, std::string>& objec,
						 boost::numeric::ublas::vector<double>& location,
						 boost::numeric::ublas::vector<double>& rotation,
						 boost::numeric::ublas::vector<double>& scale,
						 boost::numeric::ublas::vector<double>& diffuse,
						 boost::numeric::ublas::vector<double>& ambient,
						 boost::numeric::ublas::vector<double>& spec);

};


#endif //__BasicDrawable__