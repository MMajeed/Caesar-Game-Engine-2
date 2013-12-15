static const unsigned int numOfLights = 10;
static const unsigned int NumberOfTextures = 10;

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
	matrix shadowMatrix;
};

struct PS_INPUT
{
	float4 PosWVP					: SV_POSITION;
	float4 PosWorld					: POSITION;
	float4 Normal					: NORMAL1;
	float4 NormalWorld				: NORMAL2;
	float4 LightShadow[numOfLights] : LightMVP;
	float4 Color					: COLOR0;
	float3 tex						: TEXCOORD0;
};

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

Texture2DArray Shadow : register(t100);

