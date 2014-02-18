#include "Setup.fx"

// Vertex Shader
PS_INPUT VS(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT)0;

	// Combine the matrices first...
	output.PosWVP = mul(input.VertexPos, gWorldViewProj);
	
	/*output.PosWVP = input.VertexPos;
	output.PosWVP = mul(output.PosWVP, gWorld );
	output.PosWVP = mul( output.PosWVP, lightArray[0].lightView );
	output.PosWVP = mul( output.PosWVP, lightArray[0].lightProject );*/

	// Passed to the pixel shader for correct lighting:
	output.PosWorld = mul(input.VertexPos, gWorld);

	output.Normal = input.VertexNorm;

	matrix worldNoTranslation = gWorld;
	worldNoTranslation[3][0] = 0.0;
	worldNoTranslation[3][1] = 0.0;
	worldNoTranslation[3][2] = 0.0;
	output.NormalWorld = mul(input.VertexNorm, worldNoTranslation);
	output.NormalWorld = normalize(output.NormalWorld);

	// Pass the texture coordinates to the pixel shader
	output.tex = input.tex;

	return output;
}