//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer ConstantBuffer : register(b0)
{
	matrix WVP;
}

//--------------------------------------------------------------------------------------
struct VS_INPUT
{
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD;
};

struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD;
};

Texture2D Texture0      : register(t0);

SamplerState Default;

//--------------------------------------------------------------------------------------
// Vertex Shader 
//--------------------------------------------------------------------------------------
PS_INPUT VS(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT)0;
	output.Pos = mul(input.Pos, WVP);
	output.Tex = input.Tex; 

	return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader 
//--------------------------------------------------------------------------------------
float4 PS(PS_INPUT input) : SV_Target
{ 
	return Texture0.Sample(Default, input.Tex);
}