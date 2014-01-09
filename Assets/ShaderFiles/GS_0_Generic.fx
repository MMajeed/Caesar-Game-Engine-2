#include "Setup.fx"

[maxvertexcount(4)]
void GS(triangle PS_INPUT input[3], inout TriangleStream<PS_INPUT> SpriteStream)
{
	[unroll]
	for(int i = 0; i < 3; i++)
	{
		PS_INPUT output = input[i];
		SpriteStream.Append(output);
	}
	/*for(int i = 0; i < 3; i++)
	{
		PS_INPUT output = input[i];
		SpriteStream.Append(output);
	}*/
	SpriteStream.RestartStrip();
}