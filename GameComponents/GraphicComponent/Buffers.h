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
	static const int NUMBEROFLIGHTS = 10;

	struct MaterialInfo
	{
		XMFLOAT4 diffuse;
		XMFLOAT4 ambient;
		XMFLOAT4 spec;
	};

	struct CLightDesc
	{
		XMFLOAT4 pos;		
		XMFLOAT4 dir;		
		MaterialInfo material;
		XMFLOAT4 attenuation;				
		XMFLOAT4 lightPowerRangeType;	// // x = power, y = range, z = light type, w = not used
	};

	struct cbNeverChanges
	{
		XMMATRIX mCameraView;			//matrix View;
		XMMATRIX mLightView;			//matrix View;
		XMFLOAT4 eye;					//float4 eye;
		XMFLOAT4 target;				//float4 target;
		CLightDesc lights[NUMBEROFLIGHTS];
	};

	struct cbObjectConstantBuffer
	{
		XMMATRIX finalMatrix;
		MaterialInfo colour;   
	};
};
#endif //__Buffer__