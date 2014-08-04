cbuffer cbObject : register(b0)
{
	float4 Color;
};

struct PS_INPUT
{
	float4 PosWVP					: SV_POSITION;
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
	float4 txtColor = Texture.Sample(samAnisotropic, input.tex.xy);

	if(txtColor.r == 0.0f){ discard; }
	return Color; 
}