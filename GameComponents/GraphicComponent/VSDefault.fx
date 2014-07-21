cbuffer cbObject : register(b0)
{
	matrix WVP;
};


struct VS_INPUT
{
	float4 VertexPos : POSITION;
};

struct PS_INPUT
{
	float4 PosWVP : SV_POSITION;
};

// Vertex Shader
PS_INPUT VS(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT)0;

	// Combine the matrices first...
	output.PosWVP = mul(input.VertexPos, WVP);

	return output;
}