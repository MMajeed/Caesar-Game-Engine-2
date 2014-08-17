cbuffer cbObject : register(b0)
{
	float4 Diffuse;
	float4 Ambient;
	float4 Specular;
};
struct PS_INPUT
{
	float4 PosWVP					: SV_POSITION;
	float4 PosWorld					: POSITION;
	float4 Normal					: NORMAL1;
	float4 NormalWorld				: NORMAL2;
	float3 tex						: TEXCOORD0;
};

struct PS_OUTPUT
{
	float4 PosWorld				: SV_TARGET0;
	float4 NormalWorld			: SV_TARGET1;
	float4 Diffuse				: SV_TARGET2;
	float4 Ambient				: SV_TARGET3;
	float4 Specular				: SV_TARGET4;
};

PS_OUTPUT main(PS_INPUT input)
{
	PS_OUTPUT output = (PS_OUTPUT)0;

	output.PosWorld    = input.PosWorld;
	output.NormalWorld = input.NormalWorld;
	output.Diffuse     = Diffuse;
	output.Ambient     = Ambient;
	output.Specular    = Specular;
	
	return output;
}