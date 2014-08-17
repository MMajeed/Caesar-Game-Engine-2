#ifndef __GraphicModel__
#define __GraphicModel__

#include "Linker.h"

#include "COMSharedPtr.h"
#include <memory>
#include <D3D11.h>
#include <Model.h>
#include "GraphicCameraEntity.h"
#include "GraphicObjectEntity.h"
#include "VertexLayout.h"

class GraphicComponentDLL_API GraphicModel
{
protected:
	GraphicModel();
	virtual void InitVertexBuffer();
	virtual void InitIndexBuffer();
public:
	void Setup(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicObjectEntity> object);

	std::vector<VertexLayout> GetVertexLayout();
	unsigned int GetNumberFaces();

	static std::shared_ptr<GraphicModel> Spawn(std::shared_ptr<CHL::Model> model);

protected:
	COMSharedPtr<ID3D11Buffer>	pVertexBuffer;
	COMSharedPtr<ID3D11Buffer>	pIndexBuffer;
	std::vector<VertexLayout>	VertexLayoutList;
	std::shared_ptr<CHL::Model> Model;
	D3D_PRIMITIVE_TOPOLOGY		Topology;

	virtual void SetupModelLayout();
	virtual std::vector<char> GetVerticeByte();

	virtual void AddInputLayout(std::string Name, DXGI_FORMAT format, unsigned int Size);
	virtual unsigned int GetInputLayoutSize();

	std::unordered_map<std::string, COMSharedPtr<ID3D11InputLayout>> InputLayoutMap;

	COMSharedPtr<ID3D11InputLayout> GraphicModel::GetVertexLayout(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicObjectEntity> object);
};


#endif //__GraphicModel__