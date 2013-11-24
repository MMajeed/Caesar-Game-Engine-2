
SamplerState sam
{
	Filter = MAXIMUM_ANISOTROPIC;
	AddressU = Wrap;
	AddressV = Wrap;
	AddressW = Wrap;
};


static const float SMAP_SIZE = 2048.0f;
static const float SMAP_DX = 1.0f / SMAP_SIZE;

float CalcShadowFactor(float4 shadowPosH, LightDesc L)
{
	// Complete projection by doing division by w.
	shadowPosH.xyz /= shadowPosH.w;

	// Depth in NDC space.
	float depth = shadowPosH.z;

	// Texel size.
	const float dx = SMAP_DX;

	const float2 offsets[9] =
	{
		float2(-dx, -dx), float2(0.0f, -dx), float2(dx, -dx),
		float2(-dx, 0.0f), float2(0.0f, 0.0f), float2(dx, 0.0f),
		float2(-dx, +dx), float2(0.0f, +dx), float2(dx, +dx)
	};

	float sourcevals = 1.0f;
	[unroll]
	for(int i = 0; i < 9; ++i)
	{
		float2 loc = shadowPosH.xy + offsets[i];
		float depthTexture = Shadow.Sample(sam, float3(loc, L.ShadowNum)).x;
		bool inShadow = (shadowPosH.z - depthTexture) >= 0.01;
		if(inShadow == true)
		{
			sourcevals -= 0.08f;
		}
	}

	return sourcevals;
}