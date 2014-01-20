#include "Setup.fx"
SamplerState samAnisotropic
{
	Filter = MAXIMUM_ANISOTROPIC;
	AddressU = Wrap;
	AddressV = Wrap;
	AddressW = Wrap;
};

float4 PS(PS_INPUT input) : SV_Target
{
	float4 finalColor = float4(0.0, 0.0, 0.0, 1.0);

	float4 color = ObjectTextures2D[0].Sample(samAnisotropic, input.tex.xy);

	if(color.r == 0.0f){ discard; }

	return objectMaterial.Diffuse;
}