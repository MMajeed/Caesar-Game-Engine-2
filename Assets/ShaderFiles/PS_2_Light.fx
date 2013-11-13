#include "Setup.fx"

float4 PS( PS_INPUT input ) : SV_Target
{
	float4 finalLightColour = float4(0.0, 0.0, 0.0, 0.0);

	for (unsigned int index = 0; index < numOfLights; index++ )
	{
		if( lightArray[index].Type == 0 )
		{			
			continue;
		}
		else if( lightArray[index].Type == 1 ) // Parallel light
		{
			float4 toEyeW = normalize(eye - input.PosWorld);
			finalLightColour += ComputeDirectionalLight( objectMaterial, lightArray[index],
														 input.NormalWorld, toEyeW );	
		}
		else if( lightArray[index].Type == 2 ) // Point
		{
			float4 toEyeW = normalize(eye - input.PosWorld);
			finalLightColour += ComputePointLight( objectMaterial, lightArray[index],
													input.PosWorld, input.NormalWorld, toEyeW );	
		}
		else if( lightArray[index].Type == 3 ) // Spot
		{
			float4 toEyeW = normalize(eye - input.PosWorld);
			finalLightColour += ComputeSpotLight( objectMaterial, lightArray[index],
												  input.PosWorld, input.NormalWorld, toEyeW );	
		}
	}


	finalLightColour = saturate( finalLightColour );

	finalLightColour.w = objectMaterial.Diffuse.w;

	return finalLightColour;
}