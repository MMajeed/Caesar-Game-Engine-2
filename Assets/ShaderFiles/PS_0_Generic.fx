#include "Setup.fx"
#include "CalculateTexture.fx"
#include "CalculateLight.fx"

float4 PS( PS_INPUT input ) : SV_Target
{
	float4 finalColor = float4(0.0, 0.0, 0.0, 0.0);

	finalColor += Calculate2DTexture(input.tex);
	finalColor = saturate(finalColor);

	finalColor += CalculateCubeTexture((float3)input.Normal);
	finalColor = saturate(finalColor);

	if(HasLight){ finalColor += CalculateLight(input);	}
	finalColor = saturate(finalColor);

	finalColor.w = objectMaterial.Diffuse.w;
	return finalColor;
}