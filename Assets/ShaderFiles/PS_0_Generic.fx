#include "Setup.fx"
#include "CalculateTexture.fx"
#include "CalculateLight.fx"

float4 PS( PS_INPUT input ) : SV_Target
{
	float4 finalColor = float4(0.0, 0.0, 0.0, 0.0);

	finalColor += Calculate2DTexture(input.tex);
	finalColor += CalculateCubeTexture((float3)input.Normal);

	if(HasLight)
	{
		finalColor += CalculateLight(input);
	}

	finalColor = saturate(finalColor);

	return finalColor;
}