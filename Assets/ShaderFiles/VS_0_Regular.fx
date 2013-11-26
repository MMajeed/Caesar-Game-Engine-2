#include "Setup.fx"

struct VS_INPUT
{
	float4 VertexPos : POSITION;
	float4 VertexNorm : NORMAL;
	float2 tex : TEXCOORD0;
};

// Vertex Shader
PS_INPUT VS(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT)0;

	// Combine the matrices first...
	output.PosWVP = mul(input.VertexPos, gWorldViewProj);
	
	/*output.PosWVP = input.VertexPos;
	output.PosWVP = mul(output.PosWVP, gWorld );
	output.PosWVP = mul( output.PosWVP, lightArray[0].lightView );
	output.PosWVP = mul( output.PosWVP, lightArray[0].lightProject );	*/

	// Passed to the pixel shader for correct lighting:
	output.PosWorld = mul(input.VertexPos, gWorld);

	output.Normal = input.VertexNorm;

	output.NormalWorld = mul(input.VertexNorm, gWorld);
	output.NormalWorld = normalize(output.NormalWorld);

	// Pass the texture coordinates to the pixel shader
	output.tex = input.tex;

	[unroll]
	for (unsigned int i = 0; i < numOfLights; ++i)
	{
		if(lightArray[i].ShadowNum >= 0 && lightArray[i].Type != 0)
		{
			static const matrix T = matrix(
				0.5f, 0.0f, 0.0f, 0.0f,
				0.0f, -0.5f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.5f, 0.5f, 0.0f, 1.0f);

			output.LightShadow[i] = input.VertexPos;
			output.LightShadow[i] = mul(output.LightShadow[i], gWorld);
			output.LightShadow[i] = mul(output.LightShadow[i], lightArray[i].lightView);
			output.LightShadow[i] = mul(output.LightShadow[i], lightArray[i].lightProject);
			output.LightShadow[i] = mul(output.LightShadow[i], T);
		}
	}

	return output;
}