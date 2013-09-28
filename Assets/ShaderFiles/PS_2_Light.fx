#include "Setup.fx"

float4 PS( PS_INPUT input ) : SV_Target
{
	float4 finalLightColour = float4( 0.0f, 0.0f, 0.0f, 1.0f );

	for ( int index = 0; index < 10; index++ )
	{
		if ( light[index].lightPowerRangeType.z > 2.9f && light[index].lightPowerRangeType.z < 3.1f ) // Don't do light
		{			
			continue;
		}
		else if ( light[index].lightPowerRangeType.z == 0.0f ) // Parallel light
		{
			finalLightColour += ComputeDirectionalLight( objectMaterial, light[index], 
										 input.PosWorld, 
										 input.NormalWorld, eye );	
		}
		else if ( light[index].lightPowerRangeType.z == 1.0f ) // Point
		{
			finalLightColour += ComputePointLight(objectMaterial, light[index], 
									 input.PosWorld, 
									 input.NormalWorld, eye );
		}
		else if ( light[index].lightPowerRangeType.z > 1.0f ) // Point
		{
			finalLightColour += ComputeSpotLight( objectMaterial, light[index], 
									 input.PosWorld, 
									 input.NormalWorld, eye );
		}
	}


	finalLightColour = saturate( finalLightColour );

	finalLightColour.w = objectMaterial.Diffuse.w;

}