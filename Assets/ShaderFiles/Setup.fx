#include "HLSL_Light.fx"
#include "Shadow.fx"

static const unsigned int numOfLights = 25;
static const unsigned int NumberOfTextures = 10;

cbuffer cbObject : register( b0 )
{
	matrix gWorld;
    matrix gWorldViewProj;
	MaterialInfo objectMaterial;
	unsigned int NumberOf2DTextures;
	unsigned int NumberOfCubeTextures;
	unsigned int HasLight;
};

cbuffer cbInfo : register( b1 )
{
	matrix gView;
	matrix gProj;
	float4 eye;
};

cbuffer cbLight : register( b2 )
{
	LightDesc lightArray[numOfLights];
};

Texture2D Textures2D[NumberOfTextures] : register(t0);
TextureCube TexturesCube[NumberOfTextures] : register(t10);

struct PS_INPUT
{
    float4 PosWVP					: SV_POSITION;
	float4 PosWorld					: POSITION;
	float4 Normal					: NORMAL1;
	float4 NormalWorld				: NORMAL2;
	float4 LightShadow[numOfLights] : LightMVP;
    float4 Color					: COLOR0;
	float2 tex						: TEXCOORD0;
};