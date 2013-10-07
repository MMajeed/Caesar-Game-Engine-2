

bool IsInShadow(float4 lightPos,
				Texture2D depthMap,
				SamplerState shadowSampler)
{
	lightPos.xyz /= lightPos.w;

	if(lightPos.x < 1.0f && lightPos.y < 1.0f
		&& lightPos.x > 0.0f && lightPos.y > 0.0f)
	{
		float4 depthTexture = depthMap.Sample( shadowSampler, lightPos.xy);

		bool depthWithin = (lightPos.z - depthTexture.x) >= 0.0001;

		return depthWithin && (depthTexture.x < 0.99f);
	}
	else
	{
		return false;
	}
}

static const float SMAP_SIZE = 1024.0f;
static const float SMAP_DX = 1.0f / SMAP_SIZE;

float CalcShadowFactor(float4 shadowPosH,
                       Texture2D shadowMap, 
					   SamplerComparisonState samShadow)
{
	// Complete projection by doing division by w.
	shadowPosH.xyz /= shadowPosH.w;
	
	// Depth in NDC space.
	float depth = shadowPosH.z;

	// Texel size.
	const float dx = SMAP_DX;

	float percentLit = 0.0f;
	const float2 offsets[9] = 
	{
		float2(-dx,  -dx), float2(0.0f,  -dx), float2(dx,  -dx),
		float2(-dx, 0.0f), float2(0.0f, 0.0f), float2(dx, 0.0f),
		float2(-dx,  +dx), float2(0.0f,  +dx), float2(dx,  +dx)
	};

	[unroll]
	for(int i = 0; i < 9; ++i)
	{
		percentLit += shadowMap.SampleCmpLevelZero(samShadow, 
			shadowPosH.xy + offsets[i], depth).r;
	}

	return percentLit /= 9.0f;
}