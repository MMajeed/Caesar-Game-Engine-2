#include "Setup.fx"
#include "CalculateTexture.fx"

float4 PS( PS_INPUT input ) : SV_Target
{
	float4 finalLightColour = float4( 1.0f, 1.0f, 1.0f, 1.0f );
	
	float4 directionToCamera = input.PosWorld - eye;
	normalize( directionToCamera );

	float4 directionOfReflection = reflect( directionToCamera, input.Normal );

	finalLightColour = CalculateCubeTexture((float3)directionOfReflection);

	return finalLightColour;
}