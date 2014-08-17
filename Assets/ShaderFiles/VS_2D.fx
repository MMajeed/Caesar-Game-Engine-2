cbuffer cbObject : register(b0)
{
	matrix World;
	matrix View2D;
	matrix Orthogonal;
};

struct VS_INPUT
{
	float4 VertexPos : Position;
	float4 tex		 : Texture;
};

struct PS_INPUT
{
	float4 PosWVP	: SV_POSITION;
	float3 tex		: TEXCOORD0;
};

// Vertex Shader
PS_INPUT main(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT)0;

	output.PosWVP = input.VertexPos;
	output.PosWVP = mul(output.PosWVP, World);
	output.PosWVP = mul(output.PosWVP, View2D);
	output.PosWVP = mul(output.PosWVP, Orthogonal);

	// Pass the texture coordinates to the pixel shader
	output.tex = (float3)input.tex;

	return output;
}