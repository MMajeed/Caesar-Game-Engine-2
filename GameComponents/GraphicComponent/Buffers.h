#ifndef __cBuffer__
#define __cBuffer__

#include "Linker.h"

#include <string>
#include <D3D11.h>
#include <xnamath.h>
#include <vector>

class cBuffer
{
public:
	struct MaterialInfo
	{
		XMFLOAT4 diffuse;
		XMFLOAT4 ambient;
		XMFLOAT4 specular;
	};

	struct CLightDesc
	{
		XMFLOAT4 pos;		
		XMFLOAT4 dir;		
		MaterialInfo material;
		XMFLOAT4 attenuation;	
		float spot;
		float range;
		int type;
		int hasShadow;
		XMMATRIX lightView;
		XMMATRIX lightProject;
	};

	struct cbObject
	{
		XMMATRIX world;
		XMMATRIX worldViewProj;
		MaterialInfo colour;   
	};

	struct cbInfo
	{
		XMMATRIX view;
		XMMATRIX proj;
		XMFLOAT4 eye;
	};

	static const int numOfLights = 10;
	struct cbLight
	{
		CLightDesc lights[numOfLights];
	};
};
#endif //__Buffer__
