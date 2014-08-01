cbuffer cbObject : register(b0)
{
	float4 Color;
};

struct PS_INPUT
{
	float4 PosWVP					: SV_POSITION;
	float4 PosWorld					: POSITION;
	float4 Normal					: NORMAL1;
	float4 NormalWorld				: NORMAL2;
	float3 tex						: TEXCOORD0;
};

Texture2D Texture : register(t0);

SamplerState samAnisotropic
{
	Filter = MAXIMUM_ANISOTROPIC;
	AddressU = Wrap;
	AddressV = Wrap;
	AddressW = Wrap;
};

float4 main(PS_INPUT input) : SV_Target
{
	return Texture.Sample(samAnisotropic, input.tex.xy);
}