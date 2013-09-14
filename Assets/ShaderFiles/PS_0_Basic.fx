#include "Setup.fx"

float4 PS( PS_INPUT input ) : SV_Target
{
	float4 finalLightColour = objectMaterial.diffuse;

	return finalLightColour;
}