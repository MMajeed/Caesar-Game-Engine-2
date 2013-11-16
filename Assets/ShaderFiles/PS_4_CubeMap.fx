#include "Setup.fx"

float4 PS(PS_INPUT input) : SV_Target
{
	float4 texColour0 = cubeTexture01.Sample(samAnisotropic, (float3)input.Normal);

	return texColour0;
}