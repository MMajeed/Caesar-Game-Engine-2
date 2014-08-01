cbuffer cbObject : register(b0)
{
	float4 Eye;
};

struct PS_INPUT
{
	float4 PosWVP					: SV_POSITION;
	float4 PosWorld					: POSITION;
	float4 Normal					: NORMAL1;
	float4 NormalWorld				: NORMAL2;
	float3 tex						: TEXCOORD0;
};

TextureCube Texture : register(t0);

SamplerState samAnisotropic
{
	Filter = MAXIMUM_ANISOTROPIC;
	AddressU = Wrap;
	AddressV = Wrap;
	AddressW = Wrap;
};

float4 main(PS_INPUT input) : SV_Target
{
	float4 finalLightColour = float4(1.0f, 1.0f, 1.0f, 1.0f);

	float4 directionToCamera = input.PosWorld - Eye;
	directionToCamera = normalize(directionToCamera);

	float4 directionOfReflection = reflect(directionToCamera, input.Normal);
	finalLightColour = Texture.Sample(samAnisotropic, directionOfReflection.xyz);

	return finalLightColour;
}