#include "Setup.fx"

float4 PS( PS_INPUT input ) : SV_Target
{
	float4 finalLightColour = float4(0.0, 0.0, 0.0, 0.0);

	for ( int index = 0; index < numberOfLights; index++ )
	{
		if( lightArray[index].Type == 0 )
		{			
			continue;
		}
		else if( lightArray[index].Type == 1 ) // Parallel light
		{
			float3 toEyeW = normalize(eye - input.PosWorld);
			finalLightColour += ComputeDirectionalLight( objectMaterial, lightArray[index],
														 input.NormalWorld, toEyeW );	
		}
		else if( lightArray[index].Type == 2 ) // Point
		{
			float3 toEyeW = normalize(eye - input.PosWorld);
			finalLightColour += ComputePointLight( objectMaterial, lightArray[index],
													input.PosWorld, input.NormalWorld, toEyeW );	
		}
		else if( lightArray[index].Type == 3 ) // Spot
		{
			float3 toEyeW = normalize(eye - input.PosWorld);
			finalLightColour += ComputeSpotLight( objectMaterial, lightArray[index],
												  input.PosWorld, input.NormalWorld, toEyeW );	
		}
	}

	float4 texColour0 = texture00.Sample( samLinear, input.tex );

	float4 finalColor = texColour0 * finalLightColour;

	finalColor = saturate( finalColor );

	finalColor.w = objectMaterial.Diffuse.w;

	return finalColor;
}