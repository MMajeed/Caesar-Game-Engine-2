#include "Setup.fx"

float4 PS( PS_INPUT input ) : SV_Target
{
	float4 texColour0 = texture00.Sample( samAnisotropic, input.tex );

	return texColour0;
}