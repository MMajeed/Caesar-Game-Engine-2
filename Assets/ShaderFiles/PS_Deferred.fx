cbuffer cbObject : register(b0)
{
	float4 Color;
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
	float4 PosWorld					: POSITION;
	float4 NormalWorld				: NORMAL2;
};

PS_OUTPUT main(PS_INPUT input) : SV_Target
{
	PS_OUTPUT output = (PS_OUTPUT)0;

	output.PosWorld = input.PosWorld;
	output.NormalWorld = input.NormalWorld;

	return output; 
}