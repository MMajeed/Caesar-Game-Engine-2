#include "Setup.fx"

struct VS_INPUT
{
	float4 VertexPos : POSITION;
	float4 VertexNorm : NORMAL;
	float2 tex : TEXCOORD0;		
};

// Vertex Shader
PS_INPUT VS( VS_INPUT input )
{
	PS_INPUT output = (PS_INPUT)0;

	// Combine the matrices first...
	output.PosMVP = mul( input.VertexPos, World );

	// Passed to the pixel shader for correct lighting:
	output.PosWorld = mul( input.VertexPos, World );

	output.Normal = input.VertexNorm;

	output.NormalWorld = mul( input.VertexNorm, World );
	output.NormalWorld = normalize( output.NormalWorld );

	// Pass the texture coordinates to the pixel shader
	output.tex = input.tex;

    return output;
}

