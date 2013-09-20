#include "Setup.fx"

float4 PS( PS_INPUT input ) : SV_Target
{
	float4 finalLightColour = float4(1.0f, 1.0f, 1.0f, 1.0f);

	return finalLightColour;
}