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

	//float4 shadowPosH = input.LightShadow[0];
	//shadowPosH.xyz /= shadowPosH.w;
	//float depth = Shadow.Sample(sam, float3(shadowPosH.xy, 0)).x;
	////return float4(shadowPosH.z, 0.0, 0.0, 1.0);
	//bool inShadow = (shadowPosH.z - depth) >= 0.01;
	//if(inShadow == true)
	//{
	//	return float4(1.0, 0.0, 0.0, 1.0);
	//}
	//else
	//{
	//	return float4(0.0, 0.0, 0.0, 1.0);
	//}


	finalColor.w = objectMaterial.Diffuse.w;
	return finalColor;
}