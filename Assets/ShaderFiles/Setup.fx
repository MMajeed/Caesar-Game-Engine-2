#include "HLSL_4_BasicLightFunctions.fx"

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer cbObject : register( b0 )
{
    matrix World;
	MaterialInfo objectMaterial;
};

cbuffer cbNeverChanges : register( b1 )
{
    matrix CameraView;
	matrix LightView;
	float4 eye;
	float4 target;
	LightDesc light[10];		// Light type now in light description
};

cbuffer AnimMatrices : register( b2 )
{
	matrix BoneTransforms[128];
};

Texture2D texture00 : register( t0 );
Texture2D texture01 : register( t1 );
Texture2D texture02 : register( t2 );
Texture2D texture03 : register( t3 );
Texture2D texture04 : register( t4 );

TextureCube myCubeMap : register( t5 );

Texture2D Shadow : register( t10 );

//--------------------------------------------------------------------------------------
struct PS_INPUT
{
    float4 PosMVP      : SV_POSITION;
	float4 PosWorld    : POSITION;
	float4 Normal      : NORMAL1;
	float4 NormalWorld : NORMAL2;
	float4 LightMVP    : LightMVP;
    float4 Color       : COLOR0;
	float2 tex         : TEXCOORD0;
};