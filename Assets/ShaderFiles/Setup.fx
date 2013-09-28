#include "HLSL_Light.fx"

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer cbObject : register( b0 )
{
	matrix gWorld;
    matrix gWorldViewProj;
	MaterialInfo objectMaterial;
};

cbuffer cbInfo : register( b1 )
{
	matrix gView;
	matrix gProj;
	float4 eye;
};

cbuffer cbLight : register( b2 )
{
	LightDesc lights[128];
};

Texture2D texture00 : register( t0 );
Texture2D texture01 : register( t1 );
Texture2D texture02 : register( t2 );
Texture2D texture03 : register( t3 );
Texture2D texture04 : register( t4 );
TextureCube cubeTexture01 : register( t5 );
TextureCube cubeTexture02 : register( t6 );
TextureCube cubeTexture03 : register( t7 );
TextureCube cubeTexture04 : register( t8 );
TextureCube cubeTexture05 : register( t9 );


//--------------------------------------------------------------------------------------
struct PS_INPUT
{
    float4 PosWVP      : SV_POSITION;
	float4 PosWorld    : POSITION;
	float4 Normal      : NORMAL1;
	float4 NormalWorld : NORMAL2;
	float4 LightMVP    : LightMVP;
    float4 Color       : COLOR0;
	float2 tex         : TEXCOORD0;
};

SamplerState samLinear
{
	Filter   = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
	AddressW = Wrap;
};
