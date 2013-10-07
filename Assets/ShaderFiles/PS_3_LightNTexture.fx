#include "Setup.fx"

float4 PS( PS_INPUT input ) : SV_Target
{
	float4 finalLightColour = float4(0.0, 0.0, 0.0, 0.0);

	for ( int index = 0; index < numOfLights; index++ )
	{
		float shadow = 1.0f;

		bool isInShadow = lightArray[index].HasShadow && IsInShadow(input.LightShadow[index], Shadow, samShadow);
	
		if(isInShadow == true)
		{
			shadow = CalcShadowFactor(input.LightShadow[index], Shadow, samShadowComparison);
		}

		if( lightArray[index].Type == 1 ) // Parallel light
		{
			float3 toEyeW = normalize(eye - input.PosWorld);
			float4 lightColor = ComputeDirectionalLight( objectMaterial, lightArray[index],
														 input.NormalWorld, toEyeW );	

			lightColor *= shadow;
			finalLightColour += lightColor;
		}
		else if( lightArray[index].Type == 2 ) // Point
		{
			float3 toEyeW = normalize(eye - input.PosWorld);
			float4 lightColor = ComputePointLight( objectMaterial, lightArray[index],
													input.PosWorld, input.NormalWorld, toEyeW );	

			lightColor *= shadow;
			finalLightColour += lightColor;
		}
		else if( lightArray[index].Type == 3 ) // Spot
		{
			float3 toEyeW = normalize(eye - input.PosWorld);
			float4 lightColor = ComputeSpotLight( objectMaterial, lightArray[index],
												  input.PosWorld, input.NormalWorld, toEyeW );		

			lightColor *= shadow;
			finalLightColour += lightColor;
		}
	}

	float4 texColour0 = texture00.Sample( samLinear, input.tex );

	float4 finalColor = texColour0 * finalLightColour;

	finalColor = saturate( finalColor );

	finalColor.w = objectMaterial.Diffuse.w;

	return finalColor;
}