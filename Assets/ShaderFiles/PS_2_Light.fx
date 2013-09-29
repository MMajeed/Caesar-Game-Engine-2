#include "Setup.fx"

float4 PS( PS_INPUT input ) : SV_Target
{
	float4 finalLightColour = objectMaterial.Diffuse;

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
														 input.NormalWorld, eye );	
		}
		else if( lightArray[index].Type == 2 ) // Point
		{
			float3 toEyeW = normalize(eye - input.PosWorld);
			finalLightColour += ComputePointLight( objectMaterial, lightArray[index],
													input.NormalWorld, input.NormalWorld, eye );	
		}
		else if( lightArray[index].Type == 3 ) // Spot
		{
			float3 toEyeW = normalize(eye - input.PosWorld);
			finalLightColour += ComputeSpotLight( objectMaterial, lightArray[index],
												  input.NormalWorld, input.NormalWorld, eye );	
		}
	}


	finalLightColour = saturate( finalLightColour );

	finalLightColour.w = objectMaterial.Diffuse.w;

	return finalLightColour;
}