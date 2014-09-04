struct PS_INPUT
{
	float4 PosWVP					: SV_POSITION;
	float4 PosWorld					: POSITION;
	float4 Normal					: NORMAL1;
	float4 NormalWorld				: NORMAL2;
	float3 tex						: TEXCOORD0;
};

Texture2D LightTexture : register(t0);

float4 main(PS_INPUT input) : SV_Target
{
	float4 light = LightTexture.Load(float3(input.PosWVP.xy, 0.0));

	return light;
}