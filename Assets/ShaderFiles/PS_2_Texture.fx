#include "Setup.fx"
#include "CalculateTexture.fx"

float4 PS(PS_INPUT input) : SV_Target
{
	float4 finalColor = float4(0.0, 0.0, 0.0, 1.0);

	finalColor += Calculate2DTexture(input.tex.xy);
	finalColor = saturate(finalColor);

	return finalColor;
}