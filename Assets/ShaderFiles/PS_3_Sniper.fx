#include "Setup.fx"
#include "CalculateTexture.fx"

float4 PS(PS_INPUT input) : SV_Target
{
	float4 finalColor = float4(0.0, 0.0, 0.0, 1.0);

	float4 texColour1 = GlobalTextures2D[0].Sample(samAnisotropic, input.tex.xy);
	
	if(texColour1.x < 0.9)	  // closer to 'black'
	{
		finalColor += Calculate2DTexture(input.tex.xy);
		finalColor = saturate(finalColor);
		finalColor.x = 0.0f;
		finalColor.z = 0.0f;
	}

	return finalColor;
}