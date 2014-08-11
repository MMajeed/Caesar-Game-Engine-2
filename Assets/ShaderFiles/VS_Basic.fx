cbuffer cbObject : register(b0)
{
	matrix WVP;
	matrix World;
};

struct VS_INPUT
{
	float4 VertexPos : Position;
	float4 VertexNorm : Normal;
	float4 tex : Texture;
};

struct PS_INPUT
{
	float4 PosWVP					: SV_POSITION;
	float4 PosWorld					: POSITION;
	float4 Normal					: NORMAL1;
	float4 NormalWorld				: NORMAL2;
	float3 tex						: TEXCOORD0;
};

// Vertex Shader
PS_INPUT main(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT)0;

	// Combine the matrices first...
	output.PosWVP = mul(input.VertexPos, WVP);

	output.PosWorld = mul(input.VertexPos, World);

	output.Normal = input.VertexNorm;

	matrix worldNoTranslation = World;
	worldNoTranslation[3][0] = 0.0;
	worldNoTranslation[3][1] = 0.0;
	worldNoTranslation[3][2] = 0.0;
	worldNoTranslation[3][3] = 1.0;
	output.NormalWorld = mul(input.VertexNorm, worldNoTranslation);
	output.NormalWorld = normalize(output.NormalWorld);

	// Pass the texture coordinates to the pixel shader
	output.tex = input.tex.xyz;

	return output;
}