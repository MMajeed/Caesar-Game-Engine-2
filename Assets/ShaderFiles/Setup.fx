static const unsigned int numOfLights = 10;
static const unsigned int NumberOfTextures = 5;

// This is used to specify what the material property of the light and objects are
struct MaterialInfo
{
	float4 Diffuse;
	float4 Ambient;
	float4 Specular;
};

struct LightDesc
{
	MaterialInfo material;		// ambient, diffuse, spec
	float4 Position;			// Only used with point and spot
	float4 Direction;			// Only used with directional(parallel) and spot
	float4 Att;
	float Spot;
	float Range;
	int Type;
	int ShadowNum;
};

struct VS_INPUT
{
	float4 VertexPos : POSITION;
	float4 VertexNorm : NORMAL;
	float3 tex : TEXCOORD0;
};

struct PS_INPUT
{
	float4 PosWVP					: SV_POSITION;
	float4 PosWorld					: POSITION;
	float4 Normal					: NORMAL1;
	float4 NormalWorld				: NORMAL2;
	float4 Color					: COLOR0;
	float3 tex						: TEXCOORD0;
};

cbuffer cbObject : register( b0 )
{
	matrix gAnimation;
	matrix gObject;
	matrix gPhysics;
	matrix gWorld;
    matrix gWorldViewProj;
	MaterialInfo objectMaterial;
	unsigned int NumberOf2DTextures;
	unsigned int NumberOfCubeTextures;
	unsigned int HasLight;
	matrix UserData;
};

cbuffer cbWorld : register( b1 )
{
	matrix gView;
	matrix gProj;
	float4 eye;
	int NumberOfGlobal2DTexture;
	int NumberOfGlobalCubeTexture;
	matrix GlobalUserData;
	float NearZ;
	float FarZ;
};

cbuffer cbLight : register( b2 )
{
	LightDesc lightArray[numOfLights];
};

cbuffer cbLight : register(b3)
{
	matrix shadowMatrix[numOfLights];
};

Texture2D GlobalTextures2D[NumberOfTextures] : register(t0);
TextureCube GlobalTexturesCube[NumberOfTextures] : register(t5);
Texture2D ObjectTextures2D[NumberOfTextures] : register(t50);
TextureCube ObjectTexturesCube[NumberOfTextures] : register(t55);

Texture2DArray Shadow : register(t100);

